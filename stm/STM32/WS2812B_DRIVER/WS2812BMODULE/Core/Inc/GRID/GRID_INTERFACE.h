/*
 * GRID_INTERFACE.h
 *
 *  Created on: Dec 19, 2025
 *      Author: lucasnascimento
 *
 *      Description: This header file is an interface to connect GRID.cpp and native C files from STM32 API. The main file that will target this file is timers.c
 */

#ifndef SRC_GRID_GRID_INTERFACE_H_
#define SRC_GRID_GRID_INTERFACE_H_

#define PANEL_W 48
#define PANEL_H 48
#define GRID_H 96
#define GRID_W 96
#define JUMP 24

#define GRID_MASK_PORTA 0x1F0C
#define GRID_MASK_PORTB 0xF007
#define GRID_MASK_PORTC 0X1FF0
#define GRID_MASK_PORTD 0XFFFF
#define GRID_MASK_PORTE 0XFF80
#define SIZE 	8*3*48

extern uint8_t ready;

enum panel {
	panel_1_opcode = 0x00,
	panel_2_opcode = 0x01,
	panel_3_opcode = 0x02,
	panel_4_opcode= 0x03,
	portA = 0x04,
	portB = 0x05,
	portC = 0x06,
	portD = 0x07,
	portE = 0x08
};


extern uint32_t panel_1A[8*3*48];
extern uint32_t panel_1B[8*3*48];
extern uint32_t panel_1C[8*3*48];
extern uint32_t panel_1D[8*3*48];
extern uint32_t panel_1E[8*3*48];

extern uint32_t panel_2A[8*3*48];
extern uint32_t panel_2B[8*3*48];
extern uint32_t panel_2C[8*3*48];
extern uint32_t panel_2D[8*3*48];
extern uint32_t panel_2E[8*3*48];

extern uint32_t panel_3A[8*3*48];
extern uint32_t panel_3B[8*3*48];
extern uint32_t panel_3C[8*3*48];
extern uint32_t panel_3D[8*3*48];
extern uint32_t panel_3E[8*3*48];

extern uint32_t panel_4A[8*3*48];
extern uint32_t panel_4B[8*3*48];
extern uint32_t panel_4C[8*3*48];
extern uint32_t panel_4D[8*3*48];
extern uint32_t panel_4E[8*3*48];




#endif /* SRC_GRID_GRID_INTERFACE_H_ */
