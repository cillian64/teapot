# TEApot
TEApot: Tiny (or Temperamental) Environment Analyser.  A
[ukhasnet](https://www.ukhas.net) node with temperature, light, humidity, and
maybe pressure sensing.  ukhasnet node IDs `TEAnn` starting at `TEA01`.

#Structure
* `boards/` contains schematics and board layouts for KiCAD EDA 4.0.

#TEApots
* `TEA01`-`TEA10` planned for the
[Computer Laboratory](https://www.cl.cam.ac.uk/)
[DTG corridor](https://www.cl.cam.ac.uk/research/dtg/www/).

#Parts
* Micro: STM32F070F6P6
* Power: 
    * Battery: 2x AAA in series in rear-mounted holder.
    * TLV61225 boost switcher
* Sensors:
    * TEPT4400 photo-transistor for light
    * HTU21D for temperature and relative humidity
        * 3v3 power, 0.02uA asleep, 450uA converting
        * Precise and accurate temperature and relative humidity
        * I2C query interface
        * DFN package.
        * Happy with low duty cycle operation.
    * MS563702BA03-50 for pressure
        * Not worth fitting on all 10 nodes in the same building.

