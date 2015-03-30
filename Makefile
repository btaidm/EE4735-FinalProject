## Put this Makefile in your project directory---i.e., the directory
## containing the paper you are writing. Assuming you are using the
## rest of the toolchain here, you can use it to create .html, .tex,
## and .pdf output files (complete with bibliography, if present) from
## your markdown file.
## -	Change the paths at the top of the file as needed.
## -	Using `make` without arguments will generate html, tex, and pdf
## 	output files from all of the files with the designated markdown
##	extension. The default is `.md` but you can change this.
## -	You can specify an output format with `make tex`, `make pdf` or
## - 	`make html`.
## -	Doing `make clean` will remove all the .tex, .html, and .pdf files
## 	in your working directory. Make sure you do not have files in these
##	formats that you want to keep!
include paper-extras/extras.mk

export PAPER_BUILD_DIR = $(realpath $(CURDIR))/build-paper

CC 			= msp430-gcc
LD 			= msp430-gcc

DEVICE 		= msp430f2274

MSP430_DIR  = /opt/msp430-toolchain/include

DEVICE_IDIR = $(MSP430_DIR)
DEVICE_LDIR = $(MSP430_DIR)

IDIR 		= include
LDIR 		= lib

CF_ALL 		= -g -O2  -mmcu=$(DEVICE) --std=c99
LF_ALL 		= -L$(LDIR) -L$(DEVICE_LDIR) -T $(DEVICE).ld -g -mmcu=$(DEVICE) --std=c99

BUILD_PRE	:= build
MODULES 	= pinger
SRC_DIR 	:= $(addprefix src/,$(MODULES))
BUILD_DIR 	:= $(addprefix $(BUILD_PRE)/,$(MODULES))

SRC 		:= $(foreach sdir,$(SRC_DIR), $(wildcard $(sdir)/*.c))
OBJ			:= $(patsubst src/%.c,build/%.o,$(SRC))
INCLUDES	:= -I$(IDIR) -I$(DEVICE_IDIR)

vpath %.c $(SRC_DIR)

define make-goal
$1/%.o: %.c
	$(CC) $(CF_ALL) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all checkdirs clean project_proposal debug

all: checkdirs build/stalker.out

build/stalker.out: $(OBJ)
	$(LD) $(LF_ALL) $^ -o $@

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

project_proposal:
	$(MAKE) -C proposal

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C proposal $@

debug: all
	mspdebug rf2500 --fet-force-id MSP430F2274 gdb &


$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))

