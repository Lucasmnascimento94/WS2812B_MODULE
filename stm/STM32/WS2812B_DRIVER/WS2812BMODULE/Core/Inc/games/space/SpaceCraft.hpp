/*
 * Spacecraft.hpp
 *
 *  Created on: Jan 15, 2026
 *      Author: lucasnascimento
 */

#ifndef INC_GAMES_SPACE_SPACECRAFT_HPP_
#define INC_GAMES_SPACE_SPACECRAFT_HPP_

#include <space_sprites.hpp>
#include <console_interface.h>
#include <array>
#include <Ammo.hpp>

#pragma once
class SpaceGame;

extern bool my_hit_effect;

class SpaceCraft {
	public:

		int hp;
		int base_hp;
		int pwr;
		int base_pwr;
		int strength;
		int base_strength;
		int px;
		int py;
		uint32_t color;
		uint32_t effect_color;

		std::vector<Ammo *> ammo;
		SpaceGame *game;
		std::vector<std::vector<uint8_t>> *space_craft;
		uint8_t orientation;
		uint8_t direction;

		// Constructors
		explicit SpaceCraft(SpaceGame *game, std::vector<std::vector<uint8_t>> *space_craft, int px, int py);
		explicit SpaceCraft(SpaceGame *game, std::vector<std::vector<uint8_t>> *space_craft, uint8_t base_hp, uint8_t base_pwr, uint8_t base_strength, int px, int py);


		// Hit/Heal Controls
		int hitCraft(uint8_t damage); // Loose damage hp points and return the remaining hp
		int healCraft(uint8_t amount);
		int increasePwr(uint8_t amount);
		int increaseStrength(uint8_t amount);
		int decreasePwr(uint8_t amount);
		int decreaseStrength(uint8_t amount);
		int resetPwr(uint8_t amount);
		int resetStrength(uint8_t amount);

		// SpaceCraft Control
		virtual void moveSpaceCraft();
		virtual void displaySpaceCraft();
		void clearSpaceCraft(uint8_t i, uint8_t j);
		void clearSpaceCraft();

		virtual void hitEffect();

		void destroyEffect();
		std::vector<int> getPosition();
};


class MySpaceCraft : public SpaceCraft{
	protected:

	public:
		explicit MySpaceCraft(SpaceGame *game, std::vector<std::vector<uint8_t>> *space_craft, int px, int py);
		explicit MySpaceCraft(SpaceGame *game, std::vector<std::vector<uint8_t>> *space_craft, uint8_t base_hp, uint8_t base_pwr, uint8_t base_strength, int px, int py);
		void moveSpaceCraft();
		void displaySpaceCraft();
		void hitEffect();

};

class EnemySpaceCraft : public SpaceCraft{
	protected:

	public:
		explicit EnemySpaceCraft(SpaceGame *game, std::vector<std::vector<uint8_t>> *space_craft, int px, int py);
		explicit EnemySpaceCraft(SpaceGame *game, std::vector<std::vector<uint8_t>> *space_craft, uint8_t base_hp, uint8_t base_pwr, uint8_t base_strength, int px, int py);
		void moveSpaceCraft();
		void displaySpaceCraft();
};
#endif /* INC_GAMES_SPACE_SPACECRAFT_HPP_ */
