################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/xprintf/xprintf.c 

OBJS += \
./lib/xprintf/xprintf.o 

C_DEPS += \
./lib/xprintf/xprintf.d 


# Each subdirectory must supply rules for building sources it contributes
lib/xprintf/%.o: ../lib/xprintf/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -march=armv7e-m -mthumb -mlittle-endian -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DHSE_VALUE=8000000 -DUSE_STDPERIPH_DRIVER -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


