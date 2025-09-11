################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LIB/src/Flags.cpp \
../LIB/src/Modbus_Slave.cpp \
../LIB/src/ht621b.cpp 

C_SRCS += \
../LIB/src/EEPROMx.c \
../LIB/src/Gpiox.c \
../LIB/src/SM9541.c \
../LIB/src/Switch.c 

C_DEPS += \
./LIB/src/EEPROMx.d \
./LIB/src/Gpiox.d \
./LIB/src/SM9541.d \
./LIB/src/Switch.d 

OBJS += \
./LIB/src/EEPROMx.o \
./LIB/src/Flags.o \
./LIB/src/Gpiox.o \
./LIB/src/Modbus_Slave.o \
./LIB/src/SM9541.o \
./LIB/src/Switch.o \
./LIB/src/ht621b.o 

CPP_DEPS += \
./LIB/src/Flags.d \
./LIB/src/Modbus_Slave.d \
./LIB/src/ht621b.d 


# Each subdirectory must supply rules for building sources it contributes
LIB/src/%.o LIB/src/%.su LIB/src/%.cyclo: ../LIB/src/%.c LIB/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -IC:/Users/CHINH/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -IC:/Users/CHINH/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/STM32F1xx_HAL_Driver/Inc -IC:/Users/CHINH/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/CMSIS/Device/ST/STM32F1xx/Include -IC:/Users/CHINH/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/CMSIS/Include -I"D:/TEST_STM32/MTEE/Project_v5/LIB/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
LIB/src/%.o LIB/src/%.su LIB/src/%.cyclo: ../LIB/src/%.cpp LIB/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -IC:/Users/CHINH/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -IC:/Users/CHINH/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/STM32F1xx_HAL_Driver/Inc -IC:/Users/CHINH/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/CMSIS/Device/ST/STM32F1xx/Include -IC:/Users/CHINH/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/CMSIS/Include -I"D:/TEST_STM32/MTEE/Project_v5/LIB/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-LIB-2f-src

clean-LIB-2f-src:
	-$(RM) ./LIB/src/EEPROMx.cyclo ./LIB/src/EEPROMx.d ./LIB/src/EEPROMx.o ./LIB/src/EEPROMx.su ./LIB/src/Flags.cyclo ./LIB/src/Flags.d ./LIB/src/Flags.o ./LIB/src/Flags.su ./LIB/src/Gpiox.cyclo ./LIB/src/Gpiox.d ./LIB/src/Gpiox.o ./LIB/src/Gpiox.su ./LIB/src/Modbus_Slave.cyclo ./LIB/src/Modbus_Slave.d ./LIB/src/Modbus_Slave.o ./LIB/src/Modbus_Slave.su ./LIB/src/SM9541.cyclo ./LIB/src/SM9541.d ./LIB/src/SM9541.o ./LIB/src/SM9541.su ./LIB/src/Switch.cyclo ./LIB/src/Switch.d ./LIB/src/Switch.o ./LIB/src/Switch.su ./LIB/src/ht621b.cyclo ./LIB/src/ht621b.d ./LIB/src/ht621b.o ./LIB/src/ht621b.su

.PHONY: clean-LIB-2f-src

