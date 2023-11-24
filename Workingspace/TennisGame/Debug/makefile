################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
TennisGame.elf.size \

ELFCHECK += \
TennisGame.elf.elfcheck \


# All Target
all: TennisGame.elf secondary-outputs

# Tool invocations
TennisGame.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MicroBlaze gcc linker'
	mb-gcc -Wl,-T -Wl,../src/lscript.ld -L../../TennisGame_bsp/MicroBlaze/lib -mlittle-endian -mcpu=v8.40.a -mxl-soft-mul -Wl,--no-relax -Wl,--gc-sections -o "TennisGame.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

TennisGame.elf.size: TennisGame.elf
	@echo 'Invoking: MicroBlaze Print Size'
	mb-size TennisGame.elf  |tee "TennisGame.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

TennisGame.elf.elfcheck: TennisGame.elf
	@echo 'Invoking: Xilinx ELF Check'
	elfcheck TennisGame.elf -hw ../../Project_tennisgame/system.xml -pe MicroBlaze  |tee "TennisGame.elf.elfcheck"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) TennisGame.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
