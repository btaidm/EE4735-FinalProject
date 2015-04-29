# Stalker Bot

## Authors
* Tim Bradt 
* Evan Bajek

## Hardware Requirements

This is a project for the eZ430-RF2500, or other MSP430 processor that has
the following attributes:

* UART USCI
* Timer A
* Timer B
* GPIO

Other Required Hardware:

* 2 x SRF04 Ultrasonic Rangers
* 2 x TXS0104E Voltage-Level Translators
* 1 x Sabertooth 2x10 Motor Controller
* 4 Motors
* Batteries

## Modules

### main

This contains the main function. It contains the interrupts for the the 
ultrasonic rangers, as well as the drive algorithms.

### pinger

This contains the code for setting up the GPIO pins for a pinger, as well as
starting the pingers.

### uart

This contains the code for setting up the UART for communication to a computer
for data gathering. It contains helper functions for printing strings, and 
unsigned 32 bit integers.

### motor_base

This contains the code for communicating with the Sabertooth 2x10 Motor 
Controller. This includes setting the speed. It also provides helper functions
for setting speeds to both motors, spin the base, putting the motors to full 
stop, and setting both motors to full speed and half speed based on a given 
direction.

## Configuring

Configuration happens in the c files themselves by macros and constant variables.

The constants for the drive algorithm are stored the main.c file.

If the motor drive is flipped, there is a macro in motor_base.c that controls 
the proper direction.

## Building

The code can be built either with *msp430-gcc* or *IAR*.

### MSP430-GCC:

Before you compile, make sure that msp430-gcc is on the PATH and that you
change the Makefile variable 'MSP430_DIR' to `MSP430-TOOLCHAIN-PATH/include`.

Example: if *msp430-gcc* path is `/opt/msp430-toolchain/bin/msp430-gcc`, 
'MSP430_DIR' should be `/opt/msp430-toolchain/include`.

#### Compiling:

`make all` or `make`

#### Clean:

`make clean`

#### Programming:

Before programming, mspdebug must be on the PATH.

`make prog`

#### Debugging

You will need msp430-gdb or msp430-elf-gdb on PATH, choosing depending on what 
is available.

In one shell:

```shell
make clean all
mspdebug rf2500 --fet-force-id MSP430F2274 gdb
```

In another shell:
```shell
msp430-gdb build/stalker.out
target remote :2000
load
```

Then use standard GDB commands.

### IAR

Open the workspace in the IAR folder. Use the standard commands for building,programming, and debugging