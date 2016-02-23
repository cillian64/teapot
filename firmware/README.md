# Toolchain
This firmware uses the
[gcc-arm-embedded](https://launchpad.net/gcc-arm-embedded) toolchain
recommended by libopencm3.  It can be installed on recent Ubuntu:
`sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa`

`sudo apt-get update`

`sudo apt-get install gcc-arm-embedded`

# Submodules
Check out the correct version of libopencm3:
`git submodule update --init`

# Building, flashing, and debugging
Before doing anything else, build libopencm3:
`cd libopencm3`

`make`

`cd ..`

Then build and flash the firmware:
`make`

`make flash`

To debug:
`make debug`

