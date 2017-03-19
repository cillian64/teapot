#include "flash.h"
#include "ch.h"
#include "hal.h"

// Last page of Sector 15, available on 64KB models
#define FLASH_STORAGE_ADDR          ((uint32_t)0x0800fc00)
#define FLASH_KEYR_KEY1         ((uint32_t)0x45670123)
#define FLASH_KEYR_KEY2         ((uint32_t)0xcdef89ab)


static void flash_lock(void)
{
    FLASH->CR |= FLASH_CR_LOCK;
}

static void flash_unlock(void)
{
    /* Clear the unlock state. */
    FLASH->CR |= FLASH_CR_LOCK;

    /* Authorize the FPEC access. */
    FLASH->KEYR = FLASH_KEYR_KEY1;
    FLASH->KEYR = FLASH_KEYR_KEY2;
}

static uint32_t flash_get_status_flags(void)
{
    return FLASH->SR & (FLASH_SR_PGERR |
            FLASH_SR_EOP |
            FLASH_SR_WRPRTERR |
            FLASH_SR_BSY);
}

static void flash_wait_for_last_operation(void)
{
    while ((flash_get_status_flags() & FLASH_SR_BSY) == FLASH_SR_BSY);
}

static void flash_program_half_word(uint32_t address, uint16_t data)
{
    flash_wait_for_last_operation();
    FLASH->CR |= FLASH_CR_PG;
    *((volatile uint16_t *)address) = data;
    flash_wait_for_last_operation();
    FLASH->CR &= ~FLASH_CR_PG;
}

static void flash_program_word(uint32_t address, uint32_t data)
{
    flash_program_half_word(address, (uint16_t)data);
    flash_program_half_word(address+2, (uint16_t)(data>>16));
}

static void flash_erase_page(uint32_t page_address)
{
    flash_wait_for_last_operation();
    FLASH->CR |= FLASH_CR_PER;
    FLASH->AR = page_address;
    FLASH->CR |= FLASH_CR_STRT;
    flash_wait_for_last_operation();
    FLASH->CR &= ~FLASH_CR_PER;
}

/**
 * The config is stored in a flash_config_t. Write this to flash.
 * @param config Pointer to a flash_config_t containing the configuration to
 * write.
 */
void flash_write_config(flash_config_t* config)
{
    uint8_t i;
    uintptr_t* ptr;

    // Erase the current settings
    flash_unlock();
    flash_erase_page(FLASH_STORAGE_ADDR);

    // Loop through the flash_config_t word-by-word and write to flash
    ptr = (uintptr_t *)config;
    for(i = 0; i < sizeof(flash_config_t)/sizeof(uintptr_t); i++)
    {
        flash_program_word(FLASH_STORAGE_ADDR + 4*i, *ptr++);
    }

    // Relock flash
    flash_lock();
}

/**
 * Read a flash_config_t stored in flash.
 * @param config Pointer to a flash_config_t which will be written with the
 * configuration from flash memory.
 */
void flash_read_config(flash_config_t* config)
{
    uintptr_t i;
    uintptr_t* ptr;

    // Read through the flash_config_t
    ptr = (uintptr_t *)config;
    for(i = 0; i < sizeof(flash_config_t)/sizeof(uintptr_t); i++)
    {
        *ptr++ = *(uintptr_t *)(FLASH_STORAGE_ADDR + 4*i);
    }
}
