################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32U575I-EV/stm32u575i_eval.c \
../Drivers/BSP/STM32U575I-EV/stm32u575i_eval_bus.c \
../Drivers/BSP/STM32U575I-EV/stm32u575i_eval_eeprom.c \
../Drivers/BSP/STM32U575I-EV/stm32u575i_eval_io.c \
../Drivers/BSP/STM32U575I-EV/stm32u575i_eval_lcd.c \
../Drivers/BSP/STM32U575I-EV/stm32u575i_eval_sram.c 

OBJS += \
./Drivers/BSP/STM32U575I-EV/stm32u575i_eval.o \
./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_bus.o \
./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_eeprom.o \
./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_io.o \
./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_lcd.o \
./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_sram.o 

C_DEPS += \
./Drivers/BSP/STM32U575I-EV/stm32u575i_eval.d \
./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_bus.d \
./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_eeprom.d \
./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_io.d \
./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_lcd.d \
./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_sram.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32U575I-EV/%.o Drivers/BSP/STM32U575I-EV/%.su Drivers/BSP/STM32U575I-EV/%.cyclo: ../Drivers/BSP/STM32U575I-EV/%.c Drivers/BSP/STM32U575I-EV/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/Common -I../Drivers/BSP/STM32U575I-EV -I../Utilities/lcd -I../Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32U575I-2d-EV

clean-Drivers-2f-BSP-2f-STM32U575I-2d-EV:
	-$(RM) ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval.cyclo ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval.d ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval.o ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval.su ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_bus.cyclo ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_bus.d ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_bus.o ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_bus.su ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_eeprom.cyclo ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_eeprom.d ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_eeprom.o ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_eeprom.su ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_io.cyclo ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_io.d ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_io.o ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_io.su ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_lcd.cyclo ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_lcd.d ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_lcd.o ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_lcd.su ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_sram.cyclo ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_sram.d ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_sram.o ./Drivers/BSP/STM32U575I-EV/stm32u575i_eval_sram.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32U575I-2d-EV

