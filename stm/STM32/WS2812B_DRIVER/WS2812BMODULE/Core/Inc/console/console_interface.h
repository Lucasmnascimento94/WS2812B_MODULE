/*
 * console_interface.h
 *
 *  Created on: Dec 26, 2025
 *      Author: lucasnascimento
 */

#ifndef INC_CONSOLE_CONSOLE_INTERFACE_H_
#define INC_CONSOLE_CONSOLE_INTERFACE_H_


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

	PONG_CONSOLE_ACTIVE = 0X88,
	PONG_CONSOLE_INACTIVE = 0X89,

};

extern bool decouple_flag;
extern uint8_t game_flag;
extern uint8_t console_flag;
extern uint8_t direction;
extern uint8_t click;

extern uint8_t pong_console_flag;

extern uint8_t pong_ball_flag;
extern uint8_t pong_ball_flag;
#endif /* INC_CONSOLE_CONSOLE_INTERFACE_H_ */
