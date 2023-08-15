################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32U5xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/STM32U575I-EV/subdir.mk
-include Drivers/BSP/Components/tcpp0203/subdir.mk
-include Drivers/BSP/Components/ov5640/subdir.mk
-include Drivers/BSP/Components/mfxstm32l152/subdir.mk
-include Drivers/BSP/Components/m24256/subdir.mk
-include Drivers/BSP/Components/lsm6dso/subdir.mk
-include Drivers/BSP/Components/hx8347i/subdir.mk
-include Drivers/BSP/Components/cs42l51/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := DCMI_test_v2
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
DCMI_test_v2.elf \

MAP_FILES += \
DCMI_test_v2.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
DCMI_test_v2.list \


# All Target
all: main-build

# Main-build Target
main-build: DCMI_test_v2.elf secondary-outputs

# Tool invocations
DCMI_test_v2.elf DCMI_test_v2.map: $(OBJS) $(USER_OBJS) /home/gamer369/Desktop/internship/DCMI_test_v2/STM32U575AIIXQ_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "DCMI_test_v2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m33 -T"/home/gamer369/Desktop/internship/DCMI_test_v2/STM32U575AIIXQ_FLASH.ld" --specs=nosys.specs -Wl,-Map="DCMI_test_v2.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

DCMI_test_v2.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "DCMI_test_v2.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) DCMI_test_v2.elf DCMI_test_v2.list DCMI_test_v2.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
