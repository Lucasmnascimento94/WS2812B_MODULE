/*
 * pong.cpp
 *
 *  Created on: Jan 12, 2026
 *      Author: lucasnascimento
 */




#include <Pong.hpp>
#include <cstring>
#include "console.hpp"

uint8_t pong_console_flag = PONG_CONSOLE_ACTIVE;
uint8_t pong_ball_flag = PONG_CONSOLE_ACTIVE;

Pong::Pong(Player *player): Game("snake"){
	this->player = player;

	this->ball_vx = 50;
	this->ball_vy = 30;

	this->ball_i = 48;
	this->ball_j = 48;

	for(int i=0; i<96; i++){
		for(int j=91; j<96; j++){
			this->grid->pixelWrite(this->block_color, i, j);
			this->map[i][j] = PONG_BLOCK;
		}
	}


	for(int i=0; i<11;i++){
		this->grid->pixelWrite(this->pad_color, 48 - 5 + i, 0);
		this->map[48 - 5 + i][0] = PONG_PAD;
	}

	this->i = 48;

	std::string msg = "PONG CONSTRUCTOR";
	println(msg);
	MX_TIM3_Init();
	MX_TIM4_Init();
}

void Pong::start(){
	while(true){
		std::string msg = "";

		if(HAL_GPIO_ReadPin(GPIOC, J_LEFT_Pin) == GPIO_PIN_RESET || HAL_GPIO_ReadPin(GPIOC, J_RIGHT_Pin) == GPIO_PIN_RESET){
			this->walk_count++;
			if(pong_console_flag == PONG_CONSOLE_ACTIVE){
				this->move_pad();
			    TIM3->ARR = (2499/20);
			    TIM3->CNT = 0;
			    pong_console_flag = PONG_CONSOLE_INACTIVE;
			}
			//pong_console_flag = PONG_CONSOLE_INACTIVE;
			//HAL_Delay(50/(walk_count/2));
		}else{
			this->walk_count = 0;
		}

		if(pong_ball_flag == PONG_CONSOLE_ACTIVE){
			this->move_ball();
			pong_ball_flag = PONG_CONSOLE_INACTIVE;
		}
	}
}

uint8_t Pong::move_pad(){
	std::string err="";
	//uint8_t err_code = 0;

	uint8_t pad_i_center = this->i;

	// Get new promised position;
	switch (direction){
		case WALK_RIGHT:{ if((pad_i_center + 5) < 95) {pad_i_center++;} break;}
		case WALK_LEFT: {if((pad_i_center - 5) > 0){pad_i_center--;} break;}
	}

	if(pad_i_center == this->i) return PASS;

	uint8_t flag = PASS; //this->ruleCheck(i, j);
	if(flag == END) {this->gameEnd(); return END;}

	if(direction == WALK_RIGHT){

		this->grid->pixelWrite(GRB_BLACK, this->i - 5, 0);
		this->map[this->i  - 5][0] = VOID;

		this->grid->pixelWrite(this->pad_color, pad_i_center + 5, 0);
		this->map[pad_i_center + 5][0] = PONG_PAD;

	}else if (direction == WALK_LEFT){

			this->grid->pixelWrite(GRB_BLACK, this->i + 5, 0);
			this->map[this->i  + 5][0] = VOID;

			this->grid->pixelWrite(this->pad_color, pad_i_center - 5, 0);
			this->map[pad_i_center - 5][0] = PONG_PAD;
	}

	this->i = pad_i_center;
	return PASS;
}


#include <math.h>
#include <stdint.h>

static inline int8_t sgn8(int16_t x) { return (x < 0) ? -1 : 1; }
static inline int16_t iabs16(int16_t x) { return (x < 0) ? -x : x; }

uint8_t Pong::move_ball() {
    const int16_t SCALE = 256; // Q8.8: 256 == 1 cell

    uint8_t ci = this->ball_i;
    uint8_t cj = this->ball_j;

    int16_t vx = (int8_t)this->ball_vx;
    int16_t vy = (int8_t)this->ball_vy;

    // avoid 0-vector
    if (vx == 0 && vy == 0) { vx = 1; this->ball_vx = 1; }

    // magnitude
    float vmodf = sqrtf((float)(vx * vx + vy * vy));
    if (vmodf < 1.0f) vmodf = 1.0f;

    // normalized step in Q8.8 (angle only)
    int16_t step_i_fp = (int16_t)((vx * SCALE) / vmodf);
    int16_t step_j_fp = (int16_t)((vy * SCALE) / vmodf);

    // accumulate fractions
    this->ball_acc_i_fp += step_i_fp;
    this->ball_acc_j_fp += step_j_fp;

    // at most 1 cell per tick per axis
    int8_t di = 0, dj = 0;
    if (this->ball_acc_i_fp >= SCALE) { di = +1; this->ball_acc_i_fp -= SCALE; }
    else if (this->ball_acc_i_fp <= -SCALE) { di = -1; this->ball_acc_i_fp += SCALE; }

    if (this->ball_acc_j_fp >= SCALE) { dj = +1; this->ball_acc_j_fp -= SCALE; }
    else if (this->ball_acc_j_fp <= -SCALE) { dj = -1; this->ball_acc_j_fp += SCALE; }

    // compute next using signed math (important!)
    int16_t next_i = (int16_t)ci + di;
    int16_t next_j = (int16_t)cj + dj;

    // wall collisions
    this->collision_check(&next_i, &next_j);

    // commit
    this->ball_i = (uint8_t)next_i;
    this->ball_j = (uint8_t)next_j;

    // draw
	this->grid->pixelWrite(GRB_BLACK, ci, cj);
	this->grid->pixelWrite(this->pad_color, this->ball_i, this->ball_j);
    //this->clearBall(ci, cj);
    //this->displayBall(this->ball_i, this->ball_j);

    // speed still controlled by timer (use your own speed var ideally)
    float speed_div = (vmodf / 4.0f);
    if (speed_div < 1.0f) speed_div = 1.0f;
    TIM4->ARR = (uint32_t)((2499/2) / speed_div);
    TIM4->CNT = 0;

    return PASS;
}

uint8_t Pong::collision_check(int16_t *x, int16_t *y){
    const int16_t W = 96;
    const int16_t H = 96;

	if(*x >= W){
		this->ball_vx = (int8_t)(-this->ball_vx);
		this->ball_acc_i_fp = 0;
		*x = W - 1;
	}else if(*x < 0){
		this->ball_vx = (int8_t)(-this->ball_vx);
		this->ball_acc_i_fp = 0;
		*x = 0;
	}

	if(*y >= H){
		this->ball_vy = (int8_t)(-this->ball_vy);
		this->ball_acc_j_fp = 0;
		*y = H - 1;

	}else if(*y < 0){
		this->ball_vy = (int8_t)(-this->ball_vy);
		this->ball_acc_j_fp = 0;
		*y = 0;

	}else if(this->map[*x][*y] == PONG_BLOCK){
		this->map[*x][*y] = VOID;
		this->grid->pixelWrite(GRB_BLACK, *x, *y);
        *y -= 1;
        this->ball_vy = (int8_t)(-this->ball_vy);
        this->ball_acc_j_fp = 0;

	}else if(this->map[*x][*y] == PONG_PAD){
        *y += 1;
        this->ball_vy = (int8_t)(-this->ball_vy);
        this->ball_acc_j_fp = 0;

	}

	return PASS;
}

uint8_t Pong::ruleCheck(uint8_t i){
	return i == 0;
}



