/*
 * Snake.hpp
 *
 *  Created on: Nov 28, 2025
 *      Author: lucasnascimento
 */

#ifndef INC_GAMES_SNAKE_SNAKE_HPP_
#define INC_GAMES_SNAKE_SNAKE_HPP_

#include <cstdint>
#include "Game.hpp"
#include "Player.hpp"
#include <stack>
#include <vector>
#include "font.h"
#include "memory.hpp"
#include "console_interface.h"
using namespace std;

struct SnakeGameMap{
	uint8_t flag;
};

class Snake : public Game{
private:
	struct Node *head = NULL;
	struct Node *tail = NULL;
	Player *player;
	Pool mem{};

	// Colors
	uint32_t head_color = GRB_BLUE;
	uint32_t body_color = GRB_RED;

	uint32_t food_color = GRB_GREEN;

	uint32_t food_poison_color = GRB_VIOLET;

	uint32_t food_boost_speed_color = GRB_GHOST_WHITE;
	uint32_t food_divide_color = GRB_CYAN;
	uint32_t food_explode_color = GRB_DARK_RED;
	uint32_t food_boost_point_color = GRB_GOLD;
	uint32_t food_murf_speed_color = GRB_GRAY;

	// Points Calculation
	uint32_t base_point = 10;
	uint32_t point_mul = 1; // Affected by boost_point_food


public:
	explicit Snake(Player *player);
	std::array<std::array<SnakeGameMap, 96>, 96> map;

	uint8_t push(uint8_t i, uint8_t j);
	uint8_t pop();

	uint8_t ruleCheck(uint8_t i, uint8_t j);
	uint8_t food_check(uint8_t flag);
	uint8_t collision_check(Node *node);

	uint16_t getSize();
	Node *getHead();
	Node *getTail();


	void start(Player *player);
	uint8_t walk();
	void end_explodeAction();
	void end_poisonAction();
	void end_hitAction();
	void generateFood();
	void divide();
	void pointModidy();
	void invisible();
	void speedModify(uint8_t flag);
};

#endif /* INC_GAMES_SNAKE_SNAKE_HPP_ */
