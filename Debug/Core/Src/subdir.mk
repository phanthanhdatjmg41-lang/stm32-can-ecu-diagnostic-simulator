################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/app_can.c \
../Core/Src/app_command.c \
../Core/Src/app_dtc.c \
../Core/Src/app_ecu.c \
../Core/Src/app_heartbeat.c \
../Core/Src/app_log.c \
../Core/Src/app_uart.c \
../Core/Src/main.c \
../Core/Src/stm32f7xx_hal_msp.c \
../Core/Src/stm32f7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f7xx.c 

OBJS += \
./Core/Src/app_can.o \
./Core/Src/app_command.o \
./Core/Src/app_dtc.o \
./Core/Src/app_ecu.o \
./Core/Src/app_heartbeat.o \
./Core/Src/app_log.o \
./Core/Src/app_uart.o \
./Core/Src/main.o \
./Core/Src/stm32f7xx_hal_msp.o \
./Core/Src/stm32f7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f7xx.o 

C_DEPS += \
./Core/Src/app_can.d \
./Core/Src/app_command.d \
./Core/Src/app_dtc.d \
./Core/Src/app_ecu.d \
./Core/Src/app_heartbeat.d \
./Core/Src/app_log.d \
./Core/Src/app_uart.d \
./Core/Src/main.d \
./Core/Src/stm32f7xx_hal_msp.d \
./Core/Src/stm32f7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/app_can.cyclo ./Core/Src/app_can.d ./Core/Src/app_can.o ./Core/Src/app_can.su ./Core/Src/app_command.cyclo ./Core/Src/app_command.d ./Core/Src/app_command.o ./Core/Src/app_command.su ./Core/Src/app_dtc.cyclo ./Core/Src/app_dtc.d ./Core/Src/app_dtc.o ./Core/Src/app_dtc.su ./Core/Src/app_ecu.cyclo ./Core/Src/app_ecu.d ./Core/Src/app_ecu.o ./Core/Src/app_ecu.su ./Core/Src/app_heartbeat.cyclo ./Core/Src/app_heartbeat.d ./Core/Src/app_heartbeat.o ./Core/Src/app_heartbeat.su ./Core/Src/app_log.cyclo ./Core/Src/app_log.d ./Core/Src/app_log.o ./Core/Src/app_log.su ./Core/Src/app_uart.cyclo ./Core/Src/app_uart.d ./Core/Src/app_uart.o ./Core/Src/app_uart.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f7xx_hal_msp.cyclo ./Core/Src/stm32f7xx_hal_msp.d ./Core/Src/stm32f7xx_hal_msp.o ./Core/Src/stm32f7xx_hal_msp.su ./Core/Src/stm32f7xx_it.cyclo ./Core/Src/stm32f7xx_it.d ./Core/Src/stm32f7xx_it.o ./Core/Src/stm32f7xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f7xx.cyclo ./Core/Src/system_stm32f7xx.d ./Core/Src/system_stm32f7xx.o ./Core/Src/system_stm32f7xx.su

.PHONY: clean-Core-2f-Src

