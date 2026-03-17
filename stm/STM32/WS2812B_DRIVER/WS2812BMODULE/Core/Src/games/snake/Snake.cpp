/*
 * Snake.cpp
 *
 *  Created on: Nov 28, 2025
 *      Author: lucasnascimento
 */

#include "Snake.hpp"

uint8_t click = VOID_ACTION;
uint8_t direction = WALK_RIGHT;



Snake::Snake(Player *player): Game("snake"){
	int i=10;
	this->player = player;
	for(int j=0; j < 10; j++){
		this->push(i++, 24);
	}
	this->generateFood();
}


void Snake::start(Player *player){
	while(this->walk() != END){
		HAL_Delay(50);
	}
}

uint8_t Snake::walk(){
	std::string err="";
	uint8_t err_code = 0;
	uint8_t i = this->head->i;
	uint8_t j = this->head->j;

	// Get new promised position;
	switch (direction){
		case WALK_RIGHT: i = (i+1 >= 96)? 0: i+1; break;
		case WALK_LEFT: i = (i == 0)? 95: i-1; break;
		case WALK_UP: j = (j+1 >= 96)? 0: j+1;; break;
		case WALK_DOWN: j = (j == 0)? 95: j-1;  break;
	}

	uint8_t flag = this->ruleCheck(i, j);
	if(flag == END) {this->gameEnd(); return END;}

	err_code = this->push(i, j);
	if(err_code != NO_ERR){
		err = "pushErr:" + std::to_string(err_code);
		println(err);
	}

	if(flag != FOOD){
		err_code = this->pop();
		if(err_code != NO_ERR){
			err = "popErr:" + std::to_string(err_code);
			println(err);
		}
	}
	else {
		this->setCurrentScore(this->base_point*this->point_mul + this->getCurrentScore());
		this->generateFood();
		std::string msg = "Points: " + std::to_string(this->getCurrentScore());
		println(msg);
	}
	return PASS;
}

void Snake::generateFood(){
  std::uniform_int_distribution<int> dist(0, 95);
  std::uniform_int_distribution<int> dist_(0, 1000);

  for (int tries = 0; tries < 2000; ++tries) {
    uint8_t i = (uint8_t)this->random_generator.getRandom(0, GRID_W-1);
    uint8_t j = (uint8_t)this->random_generator.getRandom(0, GRID_H-1);

    uint16_t lotterry = this->random_generator.getRandom(0, 1000);

    if (this->map[i][j].flag == VOID) {

      if(lotterry % 7 == 0){
    	  this->map[i][j].flag = FOOD_POISON;
    	  this->grid.pixelWrite(this->food_poison_color, i, j);
      } else if(lotterry % 13 == 0){
    	  this->map[i][j].flag = FOOD_BOOST_SPEED;
    	  this->grid.pixelWrite(this->food_boost_speed_color, i, j);
      } else if(lotterry % 17 == 0){
    	  this->map[i][j].flag = FOOD_DIVIDE;
    	  this->grid.pixelWrite(this->food_divide_color, i, j);
      } else if(lotterry % 19 == 0){
    	  this->map[i][j].flag = FOOD_EXPLODE;
    	  this->grid.pixelWrite(this->food_explode_color, i, j);
      } else if(lotterry % 23 == 0){
    	  this->map[i][j].flag = FOOD_BOOST_POINT;
    	  this->grid.pixelWrite(this->food_boost_point_color, i, j);
      } else if(lotterry % 29 == 0){
    	  this->map[i][j].flag = FOOD_MURF_SPEED;
    	  this->grid.pixelWrite(this->food_murf_speed_color, i, j);
      } else{
    	  this->map[i][j].flag = FOOD;
    	  this->grid.pixelWrite(this->food_color, i, j);
      }
      return;
    }
  }
}

uint8_t Snake::ruleCheck(uint8_t i, uint8_t j){
	uint8_t flag = map[i][j].flag;

	// Display Animation and return flag for ending game.
	if(flag == BODY) {this->end_hitAction(); return END;}

	if(flag >= FOOD && flag <= FOOD_MURF_SPEED){
		switch (flag){
			case FOOD: 				return FOOD;
			case FOOD_POISON:  		this->end_poisonAction(); return END;
			case FOOD_BOOST_SPEED:  case FOOD_MURF_SPEED: this->speedModify(flag); break;
			case FOOD_DIVIDE: 		this->divide(); return FOOD;
			case FOOD_EXPLODE: 		this->end_explodeAction(); return END;
			case FOOD_BOOST_POINT:  this->pointModidy();  return FOOD;
		}
	}

	return PASS;
}



// ACTIONS
void Snake::end_explodeAction(){

}

void Snake::end_hitAction(){

}

void Snake::end_poisonAction(){

}

void Snake::divide(){

}

void Snake::pointModidy(){
    uint8_t a = this->random_generator.getRandom(0,9);

    switch (a){
        case 0: this->point_mul = 2;  break;
        case 1: this->point_mul = 3;  break;
        case 2: this->point_mul = 4;  break;
        case 3: this->point_mul = 5;  break;
        case 4: this->point_mul = 6;  break;
        case 5: this->point_mul = 7;  break;
        case 6: this->point_mul = 8;  break;
        case 7: this->point_mul = 9;  break;
        case 8: this->point_mul = 10; break;
        case 9: this->point_mul = 11; break;
        default: this->point_mul = 1; break;
    }
}

void Snake::invisible(){

}

void Snake::speedModify(uint8_t flag){

}


uint8_t Snake::push(uint8_t i, uint8_t j){
	uint8_t hi;
	uint8_t hj;
	if(this->mem.size != 0){
		hi = this->head->i;
		hj = this->head->j;
	}

	uint8_t flag = this->mem.push(i, j);


	if(flag == NO_ERR){
		this->head = &this->mem.pool[this->mem.top];
		if(this->mem.size == 1){this->tail = this->head;}
		else this->grid.pixelWrite(this->body_color, hi, hj);
		this->grid.pixelWrite(this->head_color, i, j);
		this->map[i][j].flag = BODY;
	}
	else printError(flag);
	return flag;
}

uint8_t Snake::pop(){
	if(this->mem.size == 0) {printError(EMPTY_LIST); return EMPTY_LIST;}
	uint8_t ti = this->tail->i;
	uint8_t tj = this->tail->j;
	uint8_t flag = this->mem.pop();

	if(flag == NO_ERR){
		this->tail = &this->mem.pool[this->mem.bot];
		this->grid.pixelWrite(GRB_BLACK, ti, tj);
		this->map[ti][tj].flag = VOID;
	}
	else printError(flag);
	return flag;
}






