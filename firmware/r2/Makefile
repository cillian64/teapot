##
## This file is part of the libopencm3 project.
##
## Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
##
## This library is free software: you can redistribute it and/or modify
## it under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this library.  If not, see <http://www.gnu.org/licenses/>.
##
## Modified for UKHAS 2014 Badge by Jon Sowman <jon@jonsowman.com>
##
## Repurposed for TEApot ukhasnet sensor node in February 2016
## by David Turner <david.w.turner@cl.cam.ac.uk>
##

BINARY = teapot

LIBS = 
SOURCES = $(filter-out $(BINARY).c, $(wildcard *.c)) ${LIBS}
OBJS = $(SOURCES:.c=.o)
GIT_COMMIT = $(shell git rev-parse --short=8 HEAD | cut -c 1-8)
#CPPFLAGS += -I../common/
CFLAGS += -std=c99 -DFIRMWARE_VERSION=\"$(GIT_COMMIT)\"

# Uncomment to use semihosting:
#LDLIBS = --specs=rdimon.specs -lm -lc -lrdimon

include Makefile.include


flash: teapot.elf
	arm-none-eabi-gdb --batch \
		-ex 'target extended-remote /dev/ttyACM0' \
		-ex 'monitor version' \
		-ex 'monitor swdp_scan' \
		-ex 'attach 1' \
		-ex 'load teapot.elf'

debug: teapot.elf
	arm-none-eabi-gdb -ex 'target extended-remote /dev/ttyACM0' \
		-ex 'monitor swdp_scan' \
		-ex 'attach 1' \
		-ex 'file teapot.elf'


