/*
 * print.hpp
 *
 *  Created on: Nov 29, 2025
 *      Author: lucasnascimento
 */

#ifndef INC_PRINT_PRINT_HPP_
#define INC_PRINT_PRINT_HPP_

#include <string>
#include <cstdint>
#include "stm32h5xx_hal.h"

enum class prinMode : uint8_t {
	INTERRUPT = 0x01,
	DMA = 0X02,
	POL = 0X03
};


void println(std::string &str);





#endif /* INC_PRINT_PRINT_HPP_ */
