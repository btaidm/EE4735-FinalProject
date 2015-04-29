# File: Makefile
# Builds stalker.out for the eZ430-rf2500

# Compiler and Linker
CC 			= msp430-gcc
LD 			= msp430-gcc

# Target Device
DEVICE 		= msp430f2274

# Toolchain Directory
MSP430_DIR  = /opt/msp430-toolchain

# Device Include and Library Dir
DEVICE_IDIR = $(MSP430_DIR)/include
DEVICE_LDIR = $(MSP430_DIR)/include

# Local Include and Library Directory
IDIR 		= include
LDIR 		= lib

# Compile Flags
CF_ALL 		= -g -O2  -mmcu=$(DEVICE) -std=c99
# Linker Flags
LF_ALL 		= -L$(LDIR) -L$(DEVICE_LDIR) -T $(DEVICE).ld -g -mmcu=$(DEVICE) -std=c99

# Output Directory
BUILD_PRE	:= build

# Modules to build
MODULES 	= pinger main motor_base uart

# Get Source Directories
SRC_DIR 	:= $(addprefix src/,$(MODULES))

# Get Build Directories
BUILD_DIR 	:= $(addprefix $(BUILD_PRE)/,$(MODULES))

# Get Source Files
SRC 		:= $(foreach sdir,$(SRC_DIR), $(wildcard $(sdir)/*.c))
OBJ			:= $(patsubst src/%.c,build/%.o,$(SRC))
INCLUDES	:= -I$(IDIR) -I$(DEVICE_IDIR)

# Set up for out of source building
vpath %.c $(SRC_DIR)

# Define the compile commands for the objects
define make-goal
$1/%.o: %.c
	$(CC) $(CF_ALL) $(INCLUDES) -c $$< -o $$@
endef

# State all the targets that don't produce anything
.PHONY: all checkdirs clean prog

# Build Everything
all: checkdirs build/stalker.out

# Build the final binary
build/stalker.out: $(OBJ)
	$(LD) $(LF_ALL) $^ -o $@

# Make Sure build directories exist
checkdirs: $(BUILD_DIR)

# Make all of the Build Directories
$(BUILD_DIR):
	@mkdir -p $@

# Clean up everything
clean:
	rm -rf $(BUILD_DIR)

# Program the eZ430-rf2500
prog: all
	mspdebug rf2500 --fet-force-id MSP430F2274 'prog build/stalker.out'

# Make all of the objects
$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))

