/*
 * console_interface.h
 *
 *  Created on: Dec 26, 2025
 *      Author: lucasnascimento
 */

#ifndef INC_CONSOLE_CONSOLE_INTERFACE_H_
#define INC_CONSOLE_CONSOLE_INTERFACE_H_
#include <stdint.h>

enum console_codes: uint8_t {
	VOID_ACTION = 0X00,
	WALK_RIGHT = 0X05,
	WALK_LEFT = 0X06,
	WALK_UP = 0X07,
	WALK_DOWN = 0X08,

	CLICK_OK = 0X09,
	CLICK_RESET = 0X0A,
	CLICK_STOP = 0X0B,

	GAME_SNAKE = 0X0C,
	GAME_PACMAN = 0X0D,
	GAME_SPACE = 0X0E,
	GAME_PONG = 0X0F,

	CONSOLE_INC = 0X10,
	CONSOLE_DEC = 0X11,
	CONSOLE_MOVF = 0X12,
	CONSOLE_MOVB = 0X13,
	CONSOLE_START = 0X14,
	CONSOLE_STOP = 0X15,
	CONSOLE_SELECT = 0X16,

	TIMEOUT = 0X50,
	TIMECOUNTING = 0X51,

	AMMO_PISTOL = 0X61,
	AMMO_DOUBLEPISTOL = 0X61,
	AMMO_TRIPLEPISTOL = 0X62,
	AMMO_ROCKET = 0X63,
	AMMO_DOUBLEROCKET = 0X63,
	AMMO_TRIPLEROCKET = 0X63,

	AMMO_BUFF_SUM = 0X64,
	AMMO_BUFF_MUL = 0X65,

	AMMO_ENEMY = 0X66,
	AMMO_MY = 0X67,

	PONG_CONSOLE_ACTIVE = 0X88,
	CONSOLE_ACTIVE = 0X88,
	PONG_CONSOLE_INACTIVE = 0X89,
	CONSOLE_INACTIVE = 0X89,



};




/*
 * Timer flags
 */

extern uint8_t effects_tim_flag; // TIM5

extern uint8_t my_shooting_tim_flag;  // TIM7
extern uint8_t my_movement_tim_flag; // TIM4

extern uint8_t general_1_tim_flag; // TIM6



extern uint8_t mycraft;

extern bool decouple_flag;
extern uint8_t game_flag;

extern uint8_t console_flag;
extern uint8_t direction;
extern uint8_t click;

extern uint8_t pong_console_flag;

extern uint8_t pong_ball_flag;
extern uint8_t pong_ball_flag;


/*
 * Console flags
 */
extern uint8_t console;



// Timers Flags

extern uint8_t tim3;
extern uint8_t tim4;
extern uint8_t tim5;
extern uint8_t tim6;
extern uint8_t tim7;
extern uint8_t tim15;
#endif /* INC_CONSOLE_CONSOLE_INTERFACE_H_ */















