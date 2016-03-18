################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/FreeRTOS/Source/croutine.c \
../lib/FreeRTOS/Source/event_groups.c \
../lib/FreeRTOS/Source/list.c \
../lib/FreeRTOS/Source/queue.c \
../lib/FreeRTOS/Source/tasks.c \
../lib/FreeRTOS/Source/timers.c 

OBJS += \
./lib/FreeRTOS/Source/croutine.o \
./lib/FreeRTOS/Source/event_groups.o \
./lib/FreeRTOS/Source/list.o \
./lib/FreeRTOS/Source/queue.o \
./lib/FreeRTOS/Source/tasks.o \
./lib/FreeRTOS/Source/timers.o 

C_DEPS += \
./lib/FreeRTOS/Source/croutine.d \
./lib/FreeRTOS/Source/event_groups.d \
./lib/FreeRTOS/Source/list.d \
./lib/FreeRTOS/Source/queue.d \
./lib/FreeRTOS/Source/tasks.d \
./lib/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
lib/FreeRTOS/Source/%.o: ../lib/FreeRTOS/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -march=armv7e-m -mthumb -mlittle-endian -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DHSE_VALUE=8000000 -DUSE_STDPERIPH_DRIVER -I"C:\workspace\CollimatorCPU\lib\CMSIS\Device\ST\STM32F4xx\Include" -I"C:\workspace\CollimatorCPU\lib\CMSIS\Include" -I"C:\workspace\CollimatorCPU\lib\FreeRTOS\Source\include" -I"C:\workspace\CollimatorCPU\lib\FreeRTOS\Source\portable\GCC\ARM_CM4F" -I"C:\workspace\CollimatorCPU\lib\STM32F4xx_StdPeriph_Driver\inc" -I"C:\workspace\CollimatorCPU\src" -I"C:\workspace\CollimatorCPU\lib\xprintf" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


