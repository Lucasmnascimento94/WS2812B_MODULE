################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/games/snake/Snake.cpp 

OBJS += \
./Core/Src/games/snake/Snake.o 

CPP_DEPS += \
./Core/Src/games/snake/Snake.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/games/snake/%.o Core/Src/games/snake/%.su Core/Src/games/snake/%.cyclo: ../Core/Src/games/snake/%.cpp Core/Src/games/snake/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Inc/games" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Inc/games/snake" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Inc/player" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Inc/records" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Src/games" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Src/games/snake" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Inc/print" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Src/print" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Src/GRID" -I"/Users/lucasnascimenti/Documents/GitHub/WS2812B_MODULE/stm/ws2812b_module/PROGRAM/WS2812B_DRIVER/WS2812BMODULE/Core/Inc/GRID" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-games-2f-snake

clean-Core-2f-Src-2f-games-2f-snake:
	-$(RM) ./Core/Src/games/snake/Snake.cyclo ./Core/Src/games/snake/Snake.d ./Core/Src/games/snake/Snake.o ./Core/Src/games/snake/Snake.su

.PHONY: clean-Core-2f-Src-2f-games-2f-snake

