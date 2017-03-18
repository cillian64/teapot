# TEApot
TEApot: Tiny Environment Analyser.  A
[ukhasnet](https://www.ukhas.net) node with various sensors.
ukhasnet node IDs `TEA0` through `TEAe`.

# Structure
* [board](board/) contains schematics and board layouts for KiCAD EDA 4
* [case](case/) contains plans for laser-cut cases for the nodes
* [firmware](firmware/) contains firmware for the various node flavours
* [software](software/) contains Python3 software for the USB gateway and
  GridEye receiver.

# Nodes
## Hardware
* Microcontroller: STM32F0 and STM32L0
* Power: AA or D alkaline cell with TLV61225 boost switcher
* Assorted sensors:
    * T: Temperature (HTU21d)
    * H: Humidity (HTU21d)
    * P: Pressure (MS5637)
    * S: Light (TEPT4400)
    * X: 8x8 thermopile array (AMG88 Grid-eye)

## Variants
* r2 was the first set manufactured.  Issues with I2C meant sensors did not
  work.  L0 variants are lower power than F0 but do not support USB.  L0
  variants include a RTC crystal.
* r3 was the second set manufactured, omitting USB but including support
  for the Grid-eye sensor and fixing I2C issues.  All boards include an RTC
  crystal.

Node | Board | Sensors | Status
---- | ----- | ------- | ------
TEA0 | r2 F0 |         | USB Gateway
TEA1 | r2 L0 |         | Repeater (needs firmware)
TEA2 | r2 L0 |         | Repeater (needs firmware)
TEA3 | r2 L0 |         | Repeater (needs antenna and firmware)
TEA4 | r2 L0 |         | Repeater (needs antenna and firmware)
TEA5 | r3    | THPS    | Mostly working
TEA6 | r3    | THPS    | Flash, radio OK
TEA7 | r3    | THPS    | Flash, radio OK
TEA8 | r3    | THPS    | Flash, radio OK
TEA9 | r3    | THPS    | Flash, radio OK
TEAa | r3    | THPSX   | Sensor is checkerboard-y?
TEAb | r3    | THPSX   | Transmits high-rate off-frequency
TEAc | r3    | THPSX   | Transmits ukhn frame every 30s
TEAd | r3    | THPSX   | Flash, radio OK
TEAe | r3    | THPSX   | Flash, radio OK
