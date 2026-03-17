/*
 * console.cpp
 *
 *  Created on: Jan 10, 2026
 *      Author: lucasnascimento
 */




#include "console.hpp"
#include "game_interface.h"
#include <cstring>
#include <cmath>
#include "draws.h"

uint8_t console_flag;
uint8_t current_char;
uint8_t console;

uint8_t mycraft = PASS;


uint8_t tim3;
uint8_t tim4;
uint8_t tim5 = TIMEOUT;
uint8_t tim6 = TIMEOUT;
uint8_t tim7 = TIMEOUT;
uint8_t tim15 = TIMEOUT;



uint8_t effects_tim_flag = TIMEOUT;

uint8_t my_shooting_tim_flag = TIMEOUT;
uint8_t my_movement_tim_flag = TIMEOUT;

uint8_t general_1_tim_flag = TIMEOUT;


bool decouple_flag = false;
bool first_char = true;

void MX_TIM3_Init(void)
{
    RCC->APB1LENR |= RCC_APB1LENR_TIM3EN;

    TIM3->CR1 = 0;          // stop
    TIM3->DIER = 0;

    TIM3->PSC = 24999;
    TIM3->ARR = 2499;
    TIM3->CNT = 0;

    TIM3->SR = 0;           // clear pending UIF
    TIM3->EGR = TIM_EGR_UG; // load PSC/ARR now

    TIM3->DIER = TIM_DIER_UIE;

    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    NVIC_EnableIRQ(TIM3_IRQn);

    TIM3->CR1 = TIM_CR1_CEN; // start (ARPE optional)
}

void MX_TIM4_Init(void)
{
    RCC->APB1LENR |= RCC_APB1LENR_TIM4EN;

    TIM4->CR1 = 0;          // stop
    TIM4->DIER = 0;

    TIM4->PSC = 24999/30;
    TIM4->ARR = (2499*3);
    TIM4->CNT = 0;

    TIM4->SR = 0;           // clear pending UIF
    TIM4->EGR = TIM_EGR_UG; // load PSC/ARR now

    TIM4->DIER = TIM_DIER_UIE;

    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
    NVIC_EnableIRQ(TIM4_IRQn);

    TIM4->CR1 = TIM_CR1_CEN; // start (ARPE optional)
}

void MX_TIM5_Init(void)
{
    RCC->APB1LENR |= RCC_APB1LENR_TIM5EN;

    TIM5->CR1 = 0;          // stop
    TIM5->DIER = 0;

    TIM5->PSC = 24999/15;
    TIM5->ARR = 2499;
    TIM5->CNT = 0;

    TIM5->SR = 0;           // clear pending UIF
    TIM5->EGR = TIM_EGR_UG; // load PSC/ARR now

    TIM5->DIER = TIM_DIER_UIE;

    HAL_NVIC_SetPriority(TIM5_IRQn, 0, 0);
    NVIC_EnableIRQ(TIM5_IRQn);

    TIM5->CR1 = TIM_CR1_CEN; // start (ARPE optional)
}

void MX_TIM6_Init(void)
{
    RCC->APB1LENR |= RCC_APB1LENR_TIM6EN;

    TIM6->CR1 = 0;          // stop
    TIM6->DIER = 0;

    TIM6->PSC = 24999/100;
    TIM6->ARR = 2499;
    TIM6->CNT = 0;

    TIM6->SR = 0;           // clear pending UIF
    TIM6->EGR = TIM_EGR_UG; // load PSC/ARR now

    TIM6->DIER = TIM_DIER_UIE;

    HAL_NVIC_SetPriority(TIM6_IRQn, 0, 0);
    NVIC_EnableIRQ(TIM6_IRQn);

    TIM6->CR1 = TIM_CR1_CEN; // start (ARPE optional)
}

void MX_TIM7_Init(void)
{
    RCC->APB1LENR |= RCC_APB1LENR_TIM7EN;

    TIM7->CR1 = 0;          // stop
    TIM7->DIER = 0;

    TIM7->PSC = 24999;
    TIM7->ARR = 2499;
    TIM7->CNT = 0;

    TIM7->SR = 0;           // clear pending UIF
    TIM7->EGR = TIM_EGR_UG; // load PSC/ARR now

    TIM7->DIER = TIM_DIER_UIE;

    HAL_NVIC_SetPriority(TIM7_IRQn, 0, 0);
    NVIC_EnableIRQ(TIM7_IRQn);

    TIM7->CR1 = TIM_CR1_CEN; // start (ARPE optional)
}

void MX_TIM15_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;

    TIM15->CR1 = 0;          // stop
    TIM15->DIER = 0;

    TIM15->PSC = 24999;
    TIM15->ARR = 2499;
    TIM15->CNT = 0;

    TIM15->SR = 0;           // clear pending UIF
    TIM15->EGR = TIM_EGR_UG; // load PSC/ARR now

    TIM15->DIER = TIM_DIER_UIE;

    HAL_NVIC_SetPriority(TIM15_IRQn, 0, 0);
    NVIC_EnableIRQ(TIM15_IRQn);

    TIM15->CR1 = TIM_CR1_CEN; // start (ARPE optional)
}



void initialAnimation(GRID &grid){

}

void displayAnimation(GRID &grid, uint8_t game_opcode, bool small){
	uint8_t x = 0;
	uint8_t y = 0;
	uint8_t block = 24;
	uint8_t draw[block][block] = {};
	uint16_t size = block*block;
	switch (game_opcode){
		case GAME_SNAKE:
			x = 0; y = 0; grid.clearPanel(panel_1_opcode); memcpy(draw, snake_arr, size);
			break;
		case GAME_PONG:
			x = 48; y = 0; grid.clearPanel(panel_2_opcode); memcpy(draw, pong_arr, size);
			break;
		case GAME_PACMAN:
			x = 0; y = 48; grid.clearPanel(panel_3_opcode); memcpy(draw, snake_arr, size);
			break;
		case GAME_SPACE:
			x = 48; y = 48; grid.clearPanel(panel_4_opcode); memcpy(draw, space_arr, size);
			break;
	}

	for(int i=0; i < block; i++){
		for(int j=0; j < block; j++){
			uint8_t pixel = draw[i][j];
			uint8_t px = i;
			uint8_t py = j;
			uint32_t color = 0;

			if(pixel == 1){color = (small)?GRB_YELLOW:GRB_RED;}
			else if(pixel == 2){color = (small)?GRB_YELLOW:GRB_LIGHT_SEA_GREEN;}
			else if(pixel == 3){color = (small)?GRB_YELLOW:GRB_BLUE;}
			else color = GRB_BLACK;

			grid.pixelWrite(color, py + 8 + x , 23 - px + 8 + y);
		}
	}
}


void displaySmall(GRID &grid, uint8_t game){
	switch (game){
		case GAME_SNAKE: displayAnimation(grid, GAME_SNAKE, true); break;
		case GAME_PACMAN: displayAnimation(grid, GAME_PACMAN, true); break;
		case GAME_PONG: displayAnimation(grid, GAME_PONG, true); break;
		case GAME_SPACE: displayAnimation(grid, GAME_SPACE, true); break;
		default: break;
	}
}

void displayBig(GRID &grid, uint8_t game){
	switch (game){
		case GAME_SNAKE: displayAnimation(grid, GAME_SNAKE, false); break;
		case GAME_PACMAN: displayAnimation(grid, GAME_PACMAN, false); break;
		case GAME_PONG: displayAnimation(grid, GAME_PONG, false); break;
		case GAME_SPACE: displayAnimation(grid, GAME_SPACE, false); break;
		default: break;
	}
}

void getName(Player &player){
	bool not_ready = true;
	println(player.name);
	player.name = std::string(12, ' ');
	uint8_t index = 0;
	current_char = ' ';
	player.name.at(index) = current_char;

	while(not_ready){
		if(console_flag != VOID_ACTION && decouple_flag){
			switch(console_flag){
				case CONSOLE_INC: current_char++; break;
				case CONSOLE_DEC: current_char--;  break;
				case CONSOLE_MOVF: index++; current_char = player.name.at(index); break;
				case CONSOLE_MOVB: if(index != 0){index--; current_char = player.name.at(index);} break;
				case CONSOLE_SELECT: not_ready = false; break;
			}

			if(current_char == (' ' - 1)){current_char = 'Z';}
			else if(current_char == (' ' + 1)){current_char = 'A';}
			else if(current_char > 'Z' || current_char < 'A'){current_char = ' ';}
			player.name.at(index) = current_char;
			println(player.name);
			TIM3->CNT = 0;
			decouple_flag = false;
		}
		console_flag = VOID_ACTION;
	}
}

uint8_t getGame(GRID &grid){
	displayAnimation(grid, GAME_SNAKE, true);
	displayAnimation(grid, GAME_PONG, true);
	displayAnimation(grid, GAME_SPACE, true);
	displayAnimation(grid, GAME_PACMAN, true);

	bool not_ready = true;

	std::string snake = "SNAKE";
	std::string pac = "PACMAN";
	std::string space = "SPACE CRAFT";
	std::string pong = "PONG";
	std::string game = "";

	uint8_t game_opcode = 0x00;
	uint8_t old_opcode = GAME_SNAKE;

	int x = 0, y = 0;
	while(not_ready){
		if(console_flag != VOID_ACTION && decouple_flag){
			switch(console_flag){
				case CONSOLE_INC: y++; break;
				case CONSOLE_DEC: y--;  break;
				case CONSOLE_MOVF: x++; break;
				case CONSOLE_MOVB: x--; break;
				case CONSOLE_SELECT: not_ready = false; break;
			}
			if(x > 1) x = 0;
			else if(x < 0) x = 1;

			if(y > 1) y = 0;
			else if(y < 0) y = 1;

			if(x == 0 && y == 0){game = snake; game_opcode = GAME_SNAKE;}
			else if(x == 1 && y == 0){game = pong; game_opcode = GAME_PONG;}
			else if(x == 0 && y == 1){game = pac; game_opcode = GAME_PACMAN;}
			else if(x == 1 && y == 1){game = space; game_opcode = GAME_SPACE;}

			println(game);

			displaySmall(grid, old_opcode);
			displayBig(grid, game_opcode);
			old_opcode = game_opcode;

			TIM3->CNT = 0;
			decouple_flag = false;
		}
		console_flag = VOID_ACTION;
	}
	return game_opcode;
}

uint8_t userStart(Player &player, GRID &grid){
	MX_TIM3_Init();

	// Display Animation to start user interaction
	initialAnimation(grid);

	// Display option for player to put his name
	getName(player);

	// Display option with animation to choose the game
	return getGame(grid);

}
