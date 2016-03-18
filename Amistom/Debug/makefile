################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include lib/xprintf/subdir.mk
-include lib/STM32F4xx_StdPeriph_Driver/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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
SECONDARY_FLASH += \
Amistom.hex \

SECONDARY_LIST += \
Amistom.lst \

SECONDARY_SIZE += \
Amistom.siz \


# All Target
all: Amistom.elf secondary-outputs

dependents:
	-cd C:/Users/mos-rk-753/amistom_test/Amistom/Release && $(MAKE) clean all

# Tool invocations
Amistom.elf: $(OBJS) $(USER_OBJS) C:/Users/mos-rk-753/amistom_test/Amistom/Release/Amistom.elf
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -ggdb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "C:\Users\mos-rk-753\amistom_test\Amistom\stm32_flash.ld" -Xlinker --gc-sections -Wl,-Map,"Amistom.map" -o "Amistom.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Amistom.hex: Amistom.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "Amistom.elf"  "Amistom.hex"
	@echo 'Finished building: $@'
	@echo ' '

Amistom.lst: Amistom.elf
	@echo 'Invoking: Cross ARM GNU Create Listing'
	arm-none-eabi-objdump --source --all-headers --demangle --line-numbers --wide "Amistom.elf" > "Amistom.lst"
	@echo 'Finished building: $@'
	@echo ' '

Amistom.siz: Amistom.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley -x --totals "Amistom.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) Amistom.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:
C:/Users/mos-rk-753/amistom_test/Amistom/Release/Amistom.elf:

-include ../makefile.targets
