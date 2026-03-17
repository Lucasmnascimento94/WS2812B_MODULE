/*
 * Ammo.hpp
 *
 *  Created on: Jan 15, 2026
 *      Author: lucasnascimento
 */

#ifndef INC_GAMES_SPACE_AMMO_HPP_
#define INC_GAMES_SPACE_AMMO_HPP_

#include <cstring>
#include <cstdint>
#include <vector>
#include <array>


#include <console_interface.h>
#include <game_interface.h>
#include <GRID.hpp>
#include <font.h>
#include <MyRandom.hpp>


struct BULLET{
	int i;
	int j;
	int power;
	int strength;
	uint8_t type;
	uint8_t orientation;
	uint32_t color;
};

extern std::vector<BULLET> bullets;

#define PISTOL_BULLET_COLOR GRB_GREEN

#pragma once
class SpaceCraft;

class Ammo{
	protected:
		SpaceCraft *space_craft;

		uint8_t ammo_type;
		int strength;
		int ammunition;
		int boost_time;
		int base_strength;
		uint8_t *orientation; // N, S, W, E, NE, NW, SE, SW


		void initRng();

	public:
		explicit Ammo(SpaceCraft *space_craft);
		virtual void shoot();

		void buffAmmo(uint8_t buff_type);
		void nerfAmmo(uint8_t nerf_type);
		void addAmmo(uint8_t amount);

		uint8_t getAmmount();


};

class Pistol : public Ammo{
	protected:
		uint32_t color = GRB_RED;
	public:
		explicit Pistol(SpaceCraft *space_craft);

		void shoot() override;
};

class DoublePistol : public Pistol{
	protected:

	public:
		explicit DoublePistol(SpaceCraft *space_craft);

		void shoot() override;

};


class TriplePistol : public Pistol{
	protected:

	public:
		explicit TriplePistol(SpaceCraft *space_craft);

		void shoot() override;
};

class Rocket : public Ammo{
	protected:
		uint32_t color = GRB_VIOLET;
	public:
		explicit Rocket(SpaceCraft *space_craft);

		void shoot() override;
};

class DoubleRocket : public Rocket{
	protected:

	public:
		explicit DoubleRocket(SpaceCraft *space_craft);

		void shoot() override;
};

class TripleRocket : public Rocket{
	protected:

	public:
		explicit TripleRocket(SpaceCraft *space_craft);

		void shoot() override;
};
#endif /* INC_GAMES_SPACE_AMMO_HPP_ */
