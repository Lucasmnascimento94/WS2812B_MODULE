/*
 * Print.cpp
 *
 *  Created on: Nov 29, 2025
 *      Author: lucasnascimento
 */


#include "Print.hpp"
#include "stm32h5xx_hal.h"

extern UART_HandleTypeDef huart4;

void println(std::string &str){
	// Send data out

	int len = str.size();
	HAL_UART_Transmit(&huart4, (uint8_t *)str.c_str(),len,1000);
	HAL_UART_Transmit(&huart4, (uint8_t *)"\n", 1, 1000);
}
