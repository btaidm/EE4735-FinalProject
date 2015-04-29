CC 			= msp430-gcc
LD 			= msp430-gcc

DEVICE 		= msp430f2274

MSP430_DIR  = /opt/msp430-toolchain/include

DEVICE_IDIR = $(MSP430_DIR)
DEVICE_LDIR = $(MSP430_DIR)

IDIR 		= include
LDIR 		= lib

CF_ALL 		= -g -O2  -mmcu=$(DEVICE) -std=c99
LF_ALL 		= -L$(LDIR) -L$(DEVICE_LDIR) -T $(DEVICE).ld -g -mmcu=$(DEVICE) -std=c99

BUILD_PRE	:= build
MODULES 	= pinger main motor_base uart
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

clean:
	rm -rf $(BUILD_DIR)

prog: all
	mspdebug rf2500 --fet-force-id MSP430F2274 'prog build/stalker.out'


$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))

