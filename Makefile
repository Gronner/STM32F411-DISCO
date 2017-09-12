# Project Name
PROJ_NAME = STM32FDISCO
# ST-Link directory
STLINK = /home/felix/Dokumente/Programme/C/MCUs/STM32F401C_DISCO/stlink
# STM32F4 library code
STM_COMMON = /home/felix/Dokumente/Programme/C/MCUs/STM32F401C_DISCO/stm32_discovery_arm_gcc/STM32F4-Discovery_FW_V1.1.0
# Directories
SRCDIR = ./src
ARMDIR = $(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src
LIBDIR = ./libs
HEADDIR = ./include
BUILDDIR = ./build

# ---- Compiler ----
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
# ---- GCC Flags ----
# Generate debug symbols, Optimize for size, 
CFLAGS = -g -Os -Wall -Tstm32_flash.ld -Werror
# Generate little-endian code, Use Thumb instruction set, set target ARM processor, allows interwork between arm and thumb instruction set
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
# Use Hardware float instructions
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 
# ---- Includes ----
CFLAGS += -I $(LIBDIR)/include
CFLAGS += -I $(HEADDIR)
CFLAGS += -I $(STM_COMMON)/Utilities/STM32F4-Discovery
CFLAGS += -I $(STM_COMMON)/Libraries/CMSIS/Include
CFLAGS += -I $(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Include
CFLAGS += -I $(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/inc

# ---- Defines ----
# Define External Clock Speed
CFLAGS += -D USE_STDPERIPH_DRIVER

# ---- Source Files ----
SRCS = $(wildcard $(SRCDIR)/*.c)
SRCS += $(wildcard $(LIBDIR)/src/*.c)
SRCS += $(wildcard $(ARMDIR)/*.c)
# STM32F4 Startup File
SRCS += $(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f4xx.s
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))
OBJs += $(patsubst $(LIBDIR)/src/%.c, $(BUILDDIR)/%.o, $(SRCS))
OBJs += $(patsubst $(ARMDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))

.PHONY: proj
.PHONY: clean
.PHONY: burn

all: proj

proj: $(BUILDDIR)/$(PROJ_NAME).elf

clean:
	@rm -f $(BUILDDIR/*.o) $(BUILDDIR)/*.elf $(BUILDDIR)/*.hex $(BUILDDIR)/*.bin	

burn: proj
	@$(STLINK)/build/Release/st-flash write $(BUILDDIR)/$(PROJ_NAME).bin 0x8000000 

$(BUILDDIR)/$(PROJ_NAME).elf: $(SRCS)
	@$(CC) $(CFLAGS) $^ -o $@
	@$(OBJCOPY) -O ihex $(BUILDDIR)/$(PROJ_NAME).elf $(BUILDDIR)/$(PROJ_NAME).hex
	@$(OBJCOPY) -O binary $(BUILDDIR)/$(PROJ_NAME).elf $(BUILDDIR)/$(PROJ_NAME).bin

debug:
	echo $(SRCS)

