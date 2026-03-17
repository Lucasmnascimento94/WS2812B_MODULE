/*
 * space.hpp
 *
 *  Created on: Jan 14, 2026
 *      Author: lucasnascimento
 */

#ifndef INC_GAMES_SPACE_SPACEGAME_HPP_
#define INC_GAMES_SPACE_SPACEGAME_HPP_

#include "SpaceCraft.hpp"
#include "Game.hpp"
#include "memory.hpp"
#include "Ammo.hpp"

struct SpaceGameMap{
	int bullet_index;
	int enemies_space_craft_index;
	uint8_t flag;
	int i;
	int j;
};

class SpaceGame : public Game {
private:
	SpaceCraft *player_craft;
	std::vector<SpaceCraft *> enemies;

	// Points Calculation
	uint32_t base_point = 10;
	uint32_t point_mul = 1; // Affected by boost_point_food

    //void clearBall(uint8_t i, uint8_t j);

    //void displaySpaceCraft(std::vector<std::vector<uint8_t>> sprite, uint8_t i, uint8_t j, bool myCraft);
    //void clearSpaceCraft(std::vector<std::vector<uint8_t>> sprite, uint8_t i, uint8_t j);
   // void shoot(bool my_shoot);
    void updateBullets();
    uint8_t bulletCollisionResolve(BULLET *bullet_a, BULLET *bullet_b);

public:
	explicit SpaceGame(Player *player);

	std::array<std::array<SpaceGameMap, 96>, 96> map;
	 std::vector<struct BULLET> bullets;

	// a targets b
	void resolveCollision(SpaceGameMap *a, SpaceGameMap *b);

	uint8_t resolveCollision(BULLET *bullet_a, BULLET *bullet_b);
	uint8_t resolveCollision(BULLET *bullet, int space_craft_index, uint8_t space_flag);
	uint8_t resolveCollision(SpaceCraft *space_craft_a, SpaceCraft *b, uint8_t space_a_flag);
	uint8_t resolveCollision(SpaceCraft *space_craft, BULLET *bullet, uint8_t space_flag);

	void refresh(SpaceGameMap *a);

	void destroy(SpaceGameMap *a);
	void destroy(BULLET *bullet);

	void overwrite(SpaceGameMap *a, SpaceGameMap *b);
	void overwrite(BULLET *bullet_a, BULLET *bullet_b);

	void swap(BULLET *bullet);
	void clearCell(SpaceGameMap *cell);

	//uint8_t collision_check(int16_t *x, int16_t *y);

	//uint8_t move_space_craft();
	//uint8_t enemy_shoot();
	//uint8_t my_shoot();
	void print(int bullet_index);
	void print(SpaceCraft *craft);
	void print (SpaceGameMap *cell);
	void start();
	void gridRevealFLag();
};
#endif /* INC_GAMES_SPACE_SPACEGAME_HPP_ */
