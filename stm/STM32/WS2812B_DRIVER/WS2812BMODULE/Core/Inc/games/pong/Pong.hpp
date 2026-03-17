/*
 * pong.h
 *
 *  Created on: Jan 12, 2026
 *      Author: lucasnascimento
 */

#ifndef INC_GAMES_PONG_PONG_HPP_
#define INC_GAMES_PONG_PONG_HPP_

#include "Player.hpp"
#include "memory.hpp"
#include "Game.hpp"
#include <cstdint>
#include "font.h"
#include "console_interface.h"

struct PongGameMap{
	uint8_t flag;
};


class Pong : public Game{
private:
	struct Node *head = NULL;
	struct Node *tail = NULL;
	struct Node *pad = NULL;
	struct Node *ball = NULL;
	uint8_t i;

	Player *player;

	// Colors
	uint32_t pad_color = GRB_BLUE;
	uint32_t block_color = GRB_RED;
	uint32_t ball_color = GRB_YELLOW;

	uint8_t ball_i = 0;
	uint8_t ball_j = 0;
	uint8_t ball_vx = 0;
	uint8_t ball_vy = 0;

	uint8_t pad_v = 0;
	uint8_t walk_count = 0;

	// Points Calculation
	uint32_t base_point = 10;
	uint32_t point_mul = 1; // Affected by boost_point_food


	int16_t SCALE = 256;      // Q8.8 scale (1 cell = 256)
	int16_t MIN_NORM = 1;     // avoid div0
	int16_t W = 96;
	int16_t H = 96;

    int ball_acc_i_fp;
    int ball_acc_j_fp;
    void clearBall(uint8_t i, uint8_t j);
    void displayBall(uint8_t i, uint8_t j);
public:
	explicit Pong(Player *player);

	std::array<std::array<PongGameMap, 96>, 96> map;

	uint8_t push(uint8_t i, uint8_t j);
	uint8_t pop();

	uint8_t ruleCheck(uint8_t i);
	uint8_t collision_check(int16_t *x, int16_t *y);
	void initRng();
	void speedModify(uint8_t flag);


	uint8_t move_pad();
	uint8_t move_ball();
	void start();
};


#endif /* INC_GAMES_PONG_PONG_HPP_ */
