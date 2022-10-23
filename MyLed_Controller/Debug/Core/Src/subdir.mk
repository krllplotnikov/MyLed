################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ESP.c \
../Core/Src/ESP_AT.c \
../Core/Src/FFT.c \
../Core/Src/FlashPROM.c \
../Core/Src/WS2812B.c \
../Core/Src/WS2812B_CustomEffects.c \
../Core/Src/WS2812B_Effects.c \
../Core/Src/WS2812B_Presets.c \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/ESP.o \
./Core/Src/ESP_AT.o \
./Core/Src/FFT.o \
./Core/Src/FlashPROM.o \
./Core/Src/WS2812B.o \
./Core/Src/WS2812B_CustomEffects.o \
./Core/Src/WS2812B_Effects.o \
./Core/Src/WS2812B_Presets.o \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/ESP.d \
./Core/Src/ESP_AT.d \
./Core/Src/FFT.d \
./Core/Src/FlashPROM.d \
./Core/Src/WS2812B.d \
./Core/Src/WS2812B_CustomEffects.d \
./Core/Src/WS2812B_Effects.d \
./Core/Src/WS2812B_Presets.d \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM3 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"D:/LocalAndCloud/MCU/STM/Projects/MyLed/MyLed_Controller/Drivers/CMSIS/DSP/Include" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ESP.d ./Core/Src/ESP.o ./Core/Src/ESP.su ./Core/Src/ESP_AT.d ./Core/Src/ESP_AT.o ./Core/Src/ESP_AT.su ./Core/Src/FFT.d ./Core/Src/FFT.o ./Core/Src/FFT.su ./Core/Src/FlashPROM.d ./Core/Src/FlashPROM.o ./Core/Src/FlashPROM.su ./Core/Src/WS2812B.d ./Core/Src/WS2812B.o ./Core/Src/WS2812B.su ./Core/Src/WS2812B_CustomEffects.d ./Core/Src/WS2812B_CustomEffects.o ./Core/Src/WS2812B_CustomEffects.su ./Core/Src/WS2812B_Effects.d ./Core/Src/WS2812B_Effects.o ./Core/Src/WS2812B_Effects.su ./Core/Src/WS2812B_Presets.d ./Core/Src/WS2812B_Presets.o ./Core/Src/WS2812B_Presets.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

