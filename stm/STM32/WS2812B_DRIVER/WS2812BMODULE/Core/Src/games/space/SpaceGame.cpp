/*
 * Space.cpp
 *
 *  Created on: Jan 14, 2026
 *      Author: lucasnascimento
 */
#include <SpaceGame.hpp>
bool gaming = true;

uint32_t enemy_shooting_speed = 0;
uint32_t bullet_speed_general = 0;

SpaceGame::SpaceGame(Player *player): Game("space") {   // was "snake"

    // Map Initializer
    for(int i=0; i<96; i++){
        for(int j=0; j<96; j++){
            this->map[i][j].i = i;
            this->map[i][j].j = j;
            this->map[i][j].flag = VOID;
            this->map[i][j].bullet_index = -1;
            this->map[i][j].enemies_space_craft_index = -1;
        }
    }

    // Player craft
    this->player = player;
    this->player_craft = new MySpaceCraft(this, &sprite_craft_2, 48, 5);
    this->player_craft->displaySpaceCraft();

    // Enemies
    for(int i=0; i<5; i++){
    	int px = i*10 + 20;
    	int py = GRID_H - 4;
        this->enemies.push_back(new EnemySpaceCraft(this, &sprite_craft_enemy_1, px, py));
        this->map[px][py].enemies_space_craft_index = i;
        this->enemies[i]->displaySpaceCraft();
    }

    // Timers
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM5_Init();
    MX_TIM6_Init();
    MX_TIM7_Init();
    MX_TIM15_Init();
}

void SpaceGame::start(){
    while(gaming){

        // Moving MySpaceCraft around the screen // TIM4
        if(HAL_GPIO_ReadPin(GPIOC, J_LEFT_Pin) == GPIO_PIN_RESET ||
           HAL_GPIO_ReadPin(GPIOC, J_RIGHT_Pin) == GPIO_PIN_RESET ||
           HAL_GPIO_ReadPin(GPIOC, J_UP_Pin) == GPIO_PIN_RESET ||
           HAL_GPIO_ReadPin(GPIOC, J_DOWN_Pin) == GPIO_PIN_RESET){

            if(my_movement_tim_flag == TIMEOUT){
                this->player_craft->direction = direction;
                this->player_craft->moveSpaceCraft();
                TIM4->CNT = 0;
                my_movement_tim_flag = TIMECOUNTING;
            }
        }

        // My shooting // TIM7
        if(my_shooting_tim_flag == TIMEOUT){
            if(HAL_GPIO_ReadPin(GPIOC, J_A_Pin) == GPIO_PIN_RESET){
                this->player_craft->ammo[0]->shoot();
            }
            TIM7->CNT = 0;
            my_shooting_tim_flag = TIMECOUNTING;
        }

        // General Timer // TIM6
        if(general_1_tim_flag == TIMEOUT){
        	// Enemy shooting (general)
            if(enemy_shooting_speed++ > 50){
            	enemy_shooting_speed = 0;
                if (!enemies.empty()) {
                    int random = this->random_generator.getRandom(0, (int)enemies.size() - 1);
                    enemies[random]->ammo[0]->shoot();
                }
            }

            // bullets
            if(bullet_speed_general++ > 10){
            	bullet_speed_general = 0;
            	this->updateBullets();
            }

            TIM6->CNT = 0;
            general_1_tim_flag = TIMECOUNTING;
        }

        if(effects_tim_flag == TIMEOUT){

        }
        // Enemy move tick
        if(tim15 == TIMEOUT){
            for(size_t i=0; i < enemies.size(); i++){
                enemies[i]->direction = WALK_DOWN;
                // enemies[i]->moveSpaceCraft();
            }
            tim15 = TIMECOUNTING;
        }
    }
}

void SpaceGame::updateBullets(){
    // Use index loop that can handle swap-pop removals without skipping
    int i = bullets.size() - 1;

    std::string s = "i is: " + std::to_string(i);
    while(i >=0){
        int bullet_index = (int)i;

        // Current bullet position
        int cx = bullets[bullet_index].i;
        int cy = bullets[bullet_index].j;

        // Guard: if map says this cell doesn't own this bullet, fix or delete safely
        if (cx < 0 || cx >= GRID_W || cy < 0 || cy >= GRID_H) {
            // bullet already inconsistent, drop it from vector
            bullets[bullet_index] = bullets.back();
            bullets.pop_back();
            continue; // re-check same i
        }

        SpaceGameMap *a = &this->map[cx][cy];
        if (a->flag != AMMO || a->bullet_index != bullet_index) {
            // map and bullets are out of sync. safest: remove bullet from vector.
            bullets[bullet_index] = bullets.back();
            bullets.pop_back();
            continue;
        }

        // Next Position
        int nx = cx;
        int ny = cy;

        switch (bullets[bullet_index].orientation){
            case SPACECRAFT_ORIENTATION_N:  ny++; break;
            case SPACECRAFT_ORIENTATION_S:  ny--; break;
            case SPACECRAFT_ORIENTATION_E:  nx++; break;
            case SPACECRAFT_ORIENTATION_W:  nx--; break;
            case SPACECRAFT_ORIENTATION_NE: nx++; ny++; break;
            case SPACECRAFT_ORIENTATION_NW: nx--; ny++; break;
            case SPACECRAFT_ORIENTATION_SE: nx++; ny--; break;
            case SPACECRAFT_ORIENTATION_SW: nx--; ny--; break;
        }

        // Safe Guard (FIX: ny compares against GRID_H)
        if(nx >= GRID_W || nx < 0 || ny >= GRID_H || ny < 0){
            this->destroy(a);
            // destroy() swap-pops, so do NOT i++
            continue;
        }

        SpaceGameMap *b = &this->map[nx][ny];
        resolveCollision(a, b);

        i--;
    }

    // Debug
    int size = (int)bullets.size();
    if(size >= 0){
        std::string s = "bullets: " + std::to_string(size);
        println(s);
    }
}

// Convention: a targets b.
void SpaceGame::resolveCollision(SpaceGameMap *a, SpaceGameMap *b){
    int collision_flag = PASS;

    if (!a || !b) return;

    // Trivial move
    if(b->flag == VOID){
        this->overwrite(a,b);
        return;
    }

    if(b->flag == AMMO){
        if (a->bullet_index < 0 || a->bullet_index >= (int)bullets.size() ||
            b->bullet_index < 0 || b->bullet_index >= (int)bullets.size()) {
            destroy(a);
            return;
        }
        collision_flag = resolveCollision(&bullets[a->bullet_index], &bullets[b->bullet_index]);
    }
    else if(b->flag == SPACE_MYCRAFT){
        if (a->bullet_index < 0 || a->bullet_index >= (int)bullets.size()) { destroy(a); return; }
        collision_flag = resolveCollision(&bullets[a->bullet_index], 0, SPACE_MYCRAFT);
    }
    else if(b->flag == SPACE_ENEMYCRAFT){
        collision_flag = DESTROY; // bullet hits enemy cell -> destroy bullet (you can expand later)
    }

    switch (collision_flag){
        case OVERWRITE:
            destroy(b);
            overwrite(a, b);
            break;

        case DESTROY:
            destroy(a);
            break;

        case DESTROY_BOTH:
            destroy(a);
            destroy(b);
            break;

        default:
            break;
    }
}

uint8_t SpaceGame::resolveCollision(BULLET *bullet_a, BULLET *bullet_b){
    if (!bullet_a || !bullet_b) return PASS;

    while(bullet_a->strength > 0 && bullet_b->strength > 0){
        bullet_a->strength -= bullet_b->power;
        bullet_b->strength -= bullet_a->power;
    }

    if(bullet_a->strength <= 0) return (bullet_b->strength <= 0)? DESTROY_BOTH: DESTROY;
    return OVERWRITE;
}

uint8_t SpaceGame::resolveCollision(BULLET *bullet, int /*space_craft_index*/, uint8_t space_flag){
    if (!bullet) return PASS;

    if(space_flag == SPACE_MYCRAFT){
        this->player_craft->hitEffect();

        while(bullet->strength > 0 && this->player_craft->hp > 0){
            bullet->strength -= this->player_craft->pwr;
            this->player_craft->hp -= bullet->power;
        }

        std::string s = "MyCraft HP: " + std::to_string(this->player_craft->hp);
        println(s);

        if(player_craft->hp <= 0){
            player_craft->destroyEffect();
            gaming = false;
        }

        if(bullet->strength <= 0) return (this->player_craft->hp <= 0)? DESTROY_BOTH: DESTROY;
        return OVERWRITE;
    }

    return DESTROY;
}

uint8_t SpaceGame::resolveCollision(SpaceCraft * /*space_craft*/, BULLET * /*bullet*/, uint8_t /*space_flag*/){
    return PASS;
}

uint8_t SpaceGame::resolveCollision(SpaceCraft * /*space_craft_a*/, SpaceCraft * /*b*/, uint8_t /*space_a_flag*/){
    return PASS;
}

void SpaceGame::refresh(SpaceGameMap *a){
    if (!a) return;
    if (a->bullet_index < 0 || a->bullet_index >= (int)bullets.size()) return;
    this->grid.pixelWrite(bullets[a->bullet_index].color, a->i, a->j);
}

void SpaceGame::destroy(SpaceGameMap *a){
    if (!a) return;

    uint8_t flag = a->flag;

    if(flag == AMMO){
        int idx = a->bullet_index;

        // Guard
        if(idx < 0 || idx >= (int)bullets.size()){
            clearCell(a);
            return;
        }

        int last_idx = (int)bullets.size() - 1;

        // If we are not removing the last element, swap it into idx and update its map cell
        if(idx != last_idx){
            BULLET moved = bullets[last_idx];
            bullets[idx] = moved;

            // Update map position of moved bullet to point at new index
            int mi = moved.i;
            int mj = moved.j;
            if (mi >= 0 && mi < GRID_W && mj >= 0 && mj < GRID_H) {
                map[mi][mj].bullet_index = idx;
                map[mi][mj].flag = AMMO;
            }
        }

        // Clear the cell we are destroying
        clearCell(a);

        bullets.pop_back();
    }

    else if(flag == SPACE_ENEMYCRAFT){
    	int idx = a->enemies_space_craft_index;

    	// clean the map and the grid
    	enemies[idx]->clearSpaceCraft();

    	int last_idx = enemies.size() - 1;
    }
}

void SpaceGame::overwrite(SpaceGameMap *a, SpaceGameMap *b){
    if (!a || !b) return;
    if (a == b) return;
    if (b->flag != VOID) return;

    if (a->flag == AMMO){
        int idx = a->bullet_index;

        if (idx < 0 || idx >= (int)bullets.size()) {
            clearCell(a);
            return;
        }

        // Move bullet ownership from a -> b
        b->bullet_index = idx;
        b->flag = AMMO;

        // Update bullet coordinates
        bullets[idx].i = b->i;
        bullets[idx].j = b->j;

        clearCell(a);
        refresh(b);
    }
}

void SpaceGame::clearCell(SpaceGameMap *cell){
    if (!cell) return;
    cell->bullet_index = -1;
    cell->flag = VOID;
    cell->enemies_space_craft_index = -1;
    this->grid.pixelWrite(0, cell->i, cell->j);
}


void SpaceGame::gridRevealFLag(){
	for(size_t i=0; i<this->map.size(); i++){
		for(size_t j=0; j<this->map[0].size(); j++){
			if(this->map[i][j].flag == VOID){
				this->grid.pixelWrite(0, i, j);
			}
			else if(this->map[i][j].flag == SPACE_MYCRAFT){
				this->grid.pixelWrite(GRB_BLUE, i, j);
			}else if(this->map[i][j].flag == AMMO){
				this->grid.pixelWrite(GRB_RED, i, j);
			}else{
				this->grid.pixelWrite(GRB_GREEN, i, j);
			}
		}
	}
}
























