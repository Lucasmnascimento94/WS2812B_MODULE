/*
 * SpaceCraft.cpp
 *
 *  Created on: Jan 16, 2026
 *      Author: lucasnascimento
 */
#include <SpaceCraft.hpp>
#include <SpaceGame.hpp>

bool my_hit_effect = false;

SpaceCraft::SpaceCraft(SpaceGame *game, std::vector<std::vector<uint8_t>> *space_craft, int px, int py)
:px(px), py(py), game(game), space_craft(space_craft)
{
    this->base_hp = 10000;
    this->base_pwr = 1;
    this->base_strength = 1;
    this->hp = this->base_hp;
    this->pwr = this->base_pwr;
    this->ammo.push_back(new Pistol(this));
}

SpaceCraft::SpaceCraft(SpaceGame *game, std::vector<std::vector<uint8_t>> *space_craft,
                       uint8_t base_hp, uint8_t base_pwr, uint8_t base_strength, int px, int py)
:base_hp(base_hp), base_pwr(base_pwr), base_strength(base_strength),
 px(px), py(py), game(game), space_craft(space_craft)
{
    this->hp = this->base_hp;
    this->pwr = this->base_pwr;
    this->strength = this->base_strength;
}

int SpaceCraft::hitCraft(uint8_t damage){
    this->hp -= damage;
    return this->hp;
}

int SpaceCraft::healCraft(uint8_t amount){
    this->hp += amount;
    return this->hp;
}

int SpaceCraft::increasePwr(uint8_t amount){
    this->pwr += amount;
    return this->pwr;
}

int SpaceCraft::increaseStrength(uint8_t amount){
    this->strength += amount;
    return this->strength;
}

int SpaceCraft::decreasePwr(uint8_t amount){
    this->pwr -= amount;
    return this->pwr;
}

int SpaceCraft::decreaseStrength(uint8_t amount){
    this->strength -= amount;
    return this->strength;
}

int SpaceCraft::resetPwr(uint8_t /*amount*/){
    this->pwr = this->base_pwr;
    return this->pwr;
}

int SpaceCraft::resetStrength(uint8_t /*amount*/){
    this->strength = this->base_strength;
    return this->strength;
}

void SpaceCraft::moveSpaceCraft(){}
void SpaceCraft::displaySpaceCraft(){}

void SpaceCraft::clearSpaceCraft(uint8_t i, uint8_t j){
    int size_x = (int)(*this->space_craft).size();
    int size_y = (int)(*this->space_craft)[0].size();

    int init_posx = 0, init_posy = 0;

    if(size_x%2 != 0) init_posx = (i - (size_x/2));
    else             init_posx = (i - ((size_x/2) - 1));

    if(size_y%2 == 0) init_posy = (j - (size_y/2));
    else              init_posy = (j - ((size_y/2) - 1));

    if(init_posx > (GRID_W - size_x)) init_posx = GRID_W - size_x;
    if(init_posx < 0) init_posx = 0;

    if(init_posy > (GRID_H - size_y)) init_posy = GRID_H - size_y;
    if(init_posy < 0) init_posy = 0;

    for(int dx=0; dx<size_x; dx++){
        for(int dy=0; dy<size_y; dy++){
            if((*this->space_craft)[dx][dy]) this->game->grid.pixelWrite(0, init_posx + dx, init_posy + dy);
            this->game->map[init_posx + dx][init_posy + dy].flag = VOID;
        }
    }
}

void SpaceCraft::clearSpaceCraft(){
    this->clearSpaceCraft((uint8_t)this->px, (uint8_t)this->py);
}

std::vector<int> SpaceCraft::getPosition(){
    return std::vector<int>{this->px, this->py};
}

void SpaceCraft::hitEffect(){}

void SpaceCraft::destroyEffect(){
    this->game->grid.clear();
    for(int i=0; i<10;i++){
        for(int j=0; j<10;j++){
            int x = this->game->random_generator.getRandom(0, GRID_W-1);
            int y = this->game->random_generator.getRandom(0, GRID_H-1);
            this->game->grid.pixelWrite(GRB_RED, x, y);
            HAL_Delay(1);
        }
    }
}


// ---------------- MyCraft ----------------

MySpaceCraft::MySpaceCraft(SpaceGame *game, std::vector<std::vector<uint8_t>> *space_craft, int px, int py)
:SpaceCraft(game, space_craft, px , py)
{
    this->color = GRB_BLUE;
    this->orientation = SPACECRAFT_ORIENTATION_N;
    this->effect_color = GRB_VIOLET;
}

MySpaceCraft::MySpaceCraft(SpaceGame *game, std::vector<std::vector<uint8_t>> *space_craft,
                           uint8_t base_hp, uint8_t base_pwr, uint8_t base_strength, int px, int py)
:SpaceCraft(game, space_craft, base_hp, base_pwr, base_strength, px, py)
{
    this->color = GRB_BLUE;
    this->orientation = SPACECRAFT_ORIENTATION_N;
    this->effect_color = GRB_VIOLET;
}

void MySpaceCraft::moveSpaceCraft(){
    int old_i = this->px;
    int old_j = this->py;

    switch (this->direction){
        case WALK_RIGHT: this->px++; break;
        case WALK_LEFT:  this->px--; break;
        case WALK_UP:    this->py++; break;
        case WALK_DOWN:  this->py--; break;
    }

    if(this->px >= GRID_W || this->px < 0) this->px = (this->px >= GRID_W)?GRID_W-1:0;
    if(this->py >= GRID_H || this->py < 0) this->py = (this->py >= GRID_H)?GRID_H-1:0;

    if(old_i != this->px || old_j != this->py) this->clearSpaceCraft((uint8_t)old_i, (uint8_t)old_j);
    this->displaySpaceCraft();
}

void MySpaceCraft::hitEffect(){
    mycraft = SPACE_CRAFT_HIT;
    this->displaySpaceCraft();
    HAL_Delay(20);
    mycraft = PASS;
    this->displaySpaceCraft();
}

void MySpaceCraft::displaySpaceCraft(){
    int size_x = (int)(*this->space_craft).size();
    int size_y = (int)(*this->space_craft)[0].size();

    int i0 = this->px;
    int j0 = this->py;

    uint32_t color_1 = 0;
    uint32_t color_3 = 0;

    int init_posx = 0, init_posy = 0;

    if(size_x%2 != 0) init_posx = (i0 - (size_x/2));
    else             init_posx = (i0 - ((size_x/2) - 1));

    if(size_y%2 == 0) init_posy = (j0 - (size_y/2));
    else              init_posy = (j0 - ((size_y/2) - 1));

    if(init_posx > (GRID_W - size_x)) init_posx = GRID_W - size_x;
    if(init_posx < 0) init_posx = 0;

    if(init_posy > (GRID_H - size_y)) init_posy = GRID_H - size_y;
    if(init_posy < 0) init_posy = 0;

    for(int dx=0; dx<size_x; dx++){
        for(int dy=0; dy<size_y; dy++){

            int wx = init_posx + dx;
            int wy = init_posy + dy;

            if (wx >= 0 && wx < GRID_W && wy >= 0 && wy < GRID_H) {
                if(this->game->map[wx][wy].flag == AMMO){
                    int bi = this->game->map[wx][wy].bullet_index;

                    // use the game-owned bullets vector
                    if (bi >= 0 && bi < (int)this->game->bullets.size()){
                        this->hitCraft(this->game->bullets[bi].power);
                    }

                    this->game->destroy(&this->game->map[wx][wy]);
                    if(hp <= 0) this->destroyEffect();
                }
            }

            color_1 = (mycraft == PASS)? this->color : this->effect_color;
            color_3 = GRB_GREEN;

            if((*this->space_craft)[dx][dy] == 1){
                this->game->grid.pixelWrite(color_1, wx, wy);
                this->game->map[wx][wy].flag = SPACE_MYCRAFT;
            }
            else if((*this->space_craft)[dx][dy] == 3){
                this->game->grid.pixelWrite(color_3, wx, wy);
                this->game->map[wx][wy].flag = SPACE_MYCRAFT;
            }
        }
    }
}


// ---------------- Enemy ----------------

EnemySpaceCraft::EnemySpaceCraft(SpaceGame *game, std::vector<std::vector<uint8_t>> *space_craft, int px, int py)
:SpaceCraft(game, space_craft, px, py)
{
    this->color = GRB_YELLOW;
    this->orientation = SPACECRAFT_ORIENTATION_S;
}

EnemySpaceCraft::EnemySpaceCraft(SpaceGame *game, std::vector<std::vector<uint8_t>> *space_craft,
                                 uint8_t base_hp, uint8_t base_pwr, uint8_t base_strength, int px, int py)
:SpaceCraft(game, space_craft, base_hp, base_pwr, base_strength, px, py)
{
    this->color = GRB_YELLOW;
    this->orientation = SPACECRAFT_ORIENTATION_S;
}

void EnemySpaceCraft::moveSpaceCraft(){
    int old_i = this->px;
    int old_j = this->py;

    switch (this->direction){
        case WALK_RIGHT: this->px++; break;
        case WALK_LEFT:  this->px--; break;
        case WALK_UP:    this->py++; break;
        case WALK_DOWN:  this->py--; break;
    }

    if(this->px >= GRID_W || this->px < 0) this->px = (this->px >= GRID_W)?GRID_W-1:0;
    if(this->py >= GRID_H || this->py < 0) this->py = (this->py >= GRID_H)?GRID_H-1:0;

    if(old_i != this->px || old_j != this->py) this->clearSpaceCraft((uint8_t)old_i, (uint8_t)old_j);
    this->displaySpaceCraft();
}

void EnemySpaceCraft::displaySpaceCraft(){
    int size_x = (int)(*this->space_craft).size();
    int size_y = (int)(*this->space_craft)[0].size();

    int i0 = this->px;
    int j0 = this->py;

    uint32_t color_1 = 0;
    uint32_t color_3 = 0;

    int init_posx = 0, init_posy = 0;

    if(size_x%2 != 0) init_posx = (i0 - (size_x/2));
    else             init_posx = (i0 - ((size_x/2) - 1));

    if(size_y%2 == 0) init_posy = (j0 - (size_y/2));
    else              init_posy = (j0 - ((size_y/2) - 1));

    if(init_posx > (GRID_W - size_x)) init_posx = GRID_W - size_x;
    if(init_posx < 0) init_posx = 0;

    if(init_posy > (GRID_H - size_y)) init_posy = GRID_H - size_y;
    if(init_posy < 0) init_posy = 0;

    for(int dx=0; dx<size_x; dx++){
        for(int dy=0; dy<size_y; dy++){
            int wx = init_posx + dx;
            int wy = init_posy + dy;

            color_1 = this->color;
            color_3 = GRB_GREEN;

            if((*this->space_craft)[dx][dy] == 1){
                this->game->grid.pixelWrite(color_1, wx, wy);
                this->game->map[wx][wy].flag = SPACE_ENEMYCRAFT;
            }
            else if((*this->space_craft)[dx][dy] == 3){
                this->game->grid.pixelWrite(color_3, wx, wy);
                this->game->map[wx][wy].flag = SPACE_ENEMYCRAFT;
            }
        }
    }
}
