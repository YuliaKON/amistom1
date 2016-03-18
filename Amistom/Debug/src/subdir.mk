################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/button.c \
../src/display.c \
../src/globalTimer.c \
../src/io.c \
../src/main.c \
../src/meandr.c \
../src/mode.c \
../src/nvic.c \
../src/outpin.c \
../src/uart.c 

OBJS += \
./src/button.o \
./src/display.o \
./src/globalTimer.o \
./src/io.o \
./src/main.o \
./src/meandr.o \
./src/mode.o \
./src/nvic.o \
./src/outpin.o \
./src/uart.o 

C_DEPS += \
./src/button.d \
./src/display.d \
./src/globalTimer.d \
./src/io.d \
./src/main.d \
./src/meandr.d \
./src/mode.d \
./src/nvic.d \
./src/outpin.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -ggdb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DHSE_VALUE=8000000 -DUSE_STDPERIPH_DRIVER -I"C:\Users\mos-rk-753\amistom_test\Amistom\lib\CMSIS\Device\ST\STM32F4xx\Include" -I"C:\Users\mos-rk-753\amistom_test\Amistom\lib\CMSIS\Include" -I"C:\Users\mos-rk-753\amistom_test\Amistom\lib\STM32F4xx_StdPeriph_Driver\inc" -I"C:\Users\mos-rk-753\amistom_test\Amistom\src" -I"C:\Users\mos-rk-753\amistom_test\Amistom\lib\xprintf" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


