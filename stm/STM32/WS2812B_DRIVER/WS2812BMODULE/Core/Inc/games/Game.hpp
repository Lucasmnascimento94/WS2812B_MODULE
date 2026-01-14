/*
 * Game.hpp
 *
 *  Created on: Nov 28, 2025
 *      Author: lucasnascimento
 */

#ifndef INC_GAMES_GAME_HPP_
#define INC_GAMES_GAME_HPP_


#include <cstdint>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include "Player.hpp"
#include "GRID.hpp"


enum Codes : uint8_t {
	END = 0X00,
	HIT_BODY = 0X01,
	HIT_WALL = 0X02,

	FOOD = 0X03,
	FOOD_POISON = 0X04,
	FOOD_BOOST_SPEED = 0X05,
	FOOD_DIVIDE = 0X06,
	FOOD_EXPLODE = 0X07,
	FOOD_BOOST_POINT = 0X08,
	FOOD_MURF_SPEED = 0X09,

	PONG_PAD = 0XE0,
	PONG_BLOCK = 0XE1,
	BODY = 0XF0,
	VOID = 0XF1,
	PASS = 0XFF,
};



class Game {
private:
    uint32_t current_score = 0;
    uint32_t record_score;
	Player *player;
	Player record_player;
    std::string game_name;
    std::vector<std::vector<uint8_t>> game_icon;
    bool newRecord = false;
    void setGameIcon(std::string name);

public:

    uint8_t map[96][96];
    explicit Game(std::string name);
    std::mt19937 engine;
    GRID grid;
    /******************************************************************************/
    /*                        			SETTERS     		   	                  */
    /******************************************************************************/
    void setCurrentScore(uint32_t score);
    void setRecordScore(uint32_t score);
    void setRecordPname(const std::string& name);

    /******************************************************************************/
    /*                        			GETTERS     		   	                  */
    /******************************************************************************/
    uint32_t getCurrentScore(void);

    uint32_t getRecordScore(void);

    std::vector<std::vector<uint8_t>> getIcon(void){
    	return this->game_icon;
    }

    void initRng();

    void gameEnd();
    void gameBegin();
};


#endif /* INC_GAMES_GAME_HPP_ */
