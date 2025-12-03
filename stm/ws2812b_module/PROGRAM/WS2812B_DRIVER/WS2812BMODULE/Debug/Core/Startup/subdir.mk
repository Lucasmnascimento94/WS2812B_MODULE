################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32h563vgtx.s 

S_DEPS += \
./Core/Startup/startup_stm32h563vgtx.d 

OBJS += \
./Core/Startup/startup_stm32h563vgtx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m33 -g3 -DDEBUG -c -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Inc/games" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Inc/games/snake" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Inc/player" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Inc/records" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Src/games" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Src/games/snake" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Inc/print" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Src/print" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Src/GRID" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Inc/GRID" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32h563vgtx.d ./Core/Startup/startup_stm32h563vgtx.o

.PHONY: clean-Core-2f-Startup

