################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include sources/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
nrf24l01_example_non_ACK.lss \

FLASH_IMAGE += \
nrf24l01_example_non_ACK.hex \

EEPROM_IMAGE += \
nrf24l01_example_non_ACK.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: nrf24l01_example_non_ACK.elf secondary-outputs

# Tool invocations
nrf24l01_example_non_ACK.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,nrf24l01_example_non_ACK.map -mmcu=atmega128 -o "nrf24l01_example_non_ACK.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

nrf24l01_example_non_ACK.lss: nrf24l01_example_non_ACK.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S nrf24l01_example_non_ACK.elf  >"nrf24l01_example_non_ACK.lss"
	@echo 'Finished building: $@'
	@echo ' '

nrf24l01_example_non_ACK.hex: nrf24l01_example_non_ACK.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex nrf24l01_example_non_ACK.elf  "nrf24l01_example_non_ACK.hex"
	@echo 'Finished building: $@'
	@echo ' '

nrf24l01_example_non_ACK.eep: nrf24l01_example_non_ACK.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex nrf24l01_example_non_ACK.elf  "nrf24l01_example_non_ACK.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: nrf24l01_example_non_ACK.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 nrf24l01_example_non_ACK.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) nrf24l01_example_non_ACK.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
