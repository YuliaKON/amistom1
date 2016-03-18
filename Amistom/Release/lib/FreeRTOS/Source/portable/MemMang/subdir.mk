################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/FreeRTOS/Source/portable/MemMang/heap_2.c 

OBJS += \
./lib/FreeRTOS/Source/portable/MemMang/heap_2.o 

C_DEPS += \
./lib/FreeRTOS/Source/portable/MemMang/heap_2.d 


# Each subdirectory must supply rules for building sources it contributes
lib/FreeRTOS/Source/portable/MemMang/%.o: ../lib/FreeRTOS/Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -march=armv7e-m -mthumb -mlittle-endian -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DHSE_VALUE=8000000 -DUSE_STDPERIPH_DRIVER -I"C:\workspace\CollimatorCPU\lib\CMSIS\Device\ST\STM32F4xx\Include" -I"C:\workspace\CollimatorCPU\lib\CMSIS\Include" -I"C:\workspace\CollimatorCPU\lib\FreeRTOS\Source\include" -I"C:\workspace\CollimatorCPU\lib\FreeRTOS\Source\portable\GCC\ARM_CM4F" -I"C:\workspace\CollimatorCPU\lib\STM32F4xx_StdPeriph_Driver\inc" -I"C:\workspace\CollimatorCPU\src" -I"C:\workspace\CollimatorCPU\lib\xprintf" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


