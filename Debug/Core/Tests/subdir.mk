################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Tests/Test.c \
../Core/Tests/testFramework.c 

OBJS += \
./Core/Tests/Test.o \
./Core/Tests/testFramework.o 

C_DEPS += \
./Core/Tests/Test.d \
./Core/Tests/testFramework.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Tests/%.o: ../Core/Tests/%.c Core/Tests/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/tusit/STM32CubeIDE/STM32F103RB-UnitTests/Core/Tests" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Tests

clean-Core-2f-Tests:
	-$(RM) ./Core/Tests/Test.d ./Core/Tests/Test.o ./Core/Tests/testFramework.d ./Core/Tests/testFramework.o

.PHONY: clean-Core-2f-Tests

