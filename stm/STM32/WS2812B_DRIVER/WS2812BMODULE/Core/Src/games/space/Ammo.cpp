/*
 * Ammo.cpp
 *
 *  Created on: Jan 15, 2026
 *      Author: lucasnascimento
 */
#include <SpaceGame.hpp>
#include <Ammo.hpp>
#include <algorithm>
#include "timers.h"

#define FIRST_AMMUNITION 100

// ✅ REMOVE THIS BUG: no global bullets vector!
// std::vector<struct BULLET> bullets;

/*
 * Super Class - Ammo
 */
Ammo::Ammo(SpaceCraft *space_craft)
:space_craft(space_craft)
{
    this->ammunition = FIRST_AMMUNITION;
    this->boost_time = 0;
}

void Ammo::shoot(){}

void Ammo::buffAmmo(uint8_t buff_type){
    uint8_t value = (uint8_t)this->space_craft->game->random_generator.getRandom(0,10);
    uint8_t time  = (uint8_t)this->space_craft->game->random_generator.getRandom(0,1000);
    this->boost_time = time;

    switch (buff_type){
        case AMMO_BUFF_SUM: this->strength += value; break;
        case AMMO_BUFF_MUL: this->strength *= value; break;
    }
}

void Ammo::nerfAmmo(uint8_t /*buff_type*/){
    this->strength = this->base_strength;
}

void Ammo::addAmmo(uint8_t amount){
    this->ammunition += amount;
}

uint8_t Ammo::getAmmount(){
    return this->ammunition;
}

/*
 * Child Class - Pistol
 */
Pistol::Pistol(SpaceCraft *space_craft)
:Ammo(space_craft)
{
    this->ammo_type = AMMO_PISTOL;
    this->strength = 1;
    this->base_strength = 1;
}

void Pistol::shoot(){
    SpaceGame *game = this->space_craft->game;
    if (!game) return;

    // ✅ use the game-owned bullets vector
    auto &bullets = game->bullets;

    std::vector<int> space_pos = this->space_craft->getPosition();

    int init_posx = 0;
    int init_posy = 0;

    int size_y = (int)(*this->space_craft->space_craft)[0].size();

    switch (this->space_craft->orientation){
        case SPACECRAFT_ORIENTATION_N:
            init_posx = space_pos[0];
            init_posy = space_pos[1] + (size_y/2) + 2;
            break;

        case SPACECRAFT_ORIENTATION_S:
            init_posx = space_pos[0];
            init_posy = space_pos[1] - ((size_y/2) + 2);
            break;

        case SPACECRAFT_ORIENTATION_E:
        case SPACECRAFT_ORIENTATION_W:
        case SPACECRAFT_ORIENTATION_NE:
        case SPACECRAFT_ORIENTATION_NW:
        case SPACECRAFT_ORIENTATION_SE:
        case SPACECRAFT_ORIENTATION_SW:
        default:
            // not implemented yet
            return;
    }

    // ✅ bounds check BEFORE touching map
    if (init_posx < 0 || init_posx >= GRID_W || init_posy < 0 || init_posy >= GRID_H) {
        return;
    }

    // If cell is not free, don't spawn bullet (prevents creating off-map bullets / index corruption)
    if (game->map[init_posx][init_posy].flag != VOID) {
        return;
    }

    BULLET newbullet = {
        .i = init_posx,
        .j = init_posy,
        .power = 1,
        .strength = 100,
        .type = BULLET_TYPE_PISTOL,
        .orientation = this->space_craft->orientation,
        .color = this->color,
    };

    bullets.push_back(newbullet);
    int idx = (int)bullets.size() - 1;

    game->grid.pixelWrite(this->color, init_posx, init_posy);
    game->map[init_posx][init_posy].bullet_index = idx;
    game->map[init_posx][init_posy].flag = AMMO;

    std::string s = "NEW BULLET: x: " + std::to_string(init_posx) + " y: " + std::to_string(init_posy);
    println(s);
}

DoublePistol::DoublePistol(SpaceCraft *space_craft)
:Pistol(space_craft)
{
    this->ammo_type = AMMO_DOUBLEPISTOL;
}

TriplePistol::TriplePistol(SpaceCraft *space_craft)
:Pistol(space_craft)
{
    this->ammo_type = AMMO_TRIPLEPISTOL;
}


// Rockets (unchanged logic)
Rocket::Rocket(SpaceCraft *space_craft)
:Ammo(space_craft)
{
    this->ammo_type = AMMO_ROCKET;
    this->strength = 5;
    this->base_strength = 5;
}

DoubleRocket::DoubleRocket(SpaceCraft *space_craft)
:Rocket(space_craft)
{
    this->ammo_type = AMMO_DOUBLEROCKET;
}

TripleRocket::TripleRocket(SpaceCraft *space_craft)
:Rocket(space_craft)
{
    this->ammo_type = AMMO_TRIPLEROCKET;
}
