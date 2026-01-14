/*
 * console.hpp
 *
 *  Created on: Jan 10, 2026
 *      Author: lucasnascimento
 */

#ifndef INC_CONSOLE_CONSOLE_HPP_
#define INC_CONSOLE_CONSOLE_HPP_

#include <cstdint>
#include <stack>
#include <vector>
#include <random>
#include <chrono>
#include "Player.hpp"
#include "GRID.hpp"
#include "font.h"
#include "memory.hpp"
#include "console_interface.h"


void initialAnimation(GRID &grid);
void displaySnakeSmall();
void displaySnakeBig();
void displaySpaceCraftSmall();
void displaySpaceCraftBig();
void displayPacManSmall();
void displayPacManBig();
void displayPongSmall();
void displayPongBig();
void getName(Player &player);
uint8_t userStart(Player &player, GRID &grid);

void MX_TIM4_Init();
void MX_TIM3_Init();

#endif /* INC_CONSOLE_CONSOLE_HPP_ */
