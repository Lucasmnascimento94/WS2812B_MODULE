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

using namespace std;

class Game {
private:
    uint32_t current_score = 0;
    uint32_t record_score  = 0;

    std::string record_pName;
    std::string game_name;
    std::vector<std::vector<uint8_t>> game_icon;
    bool newRecord = false;

    void setGameIcon(const string& name);

public:
    explicit Game(string& name);

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

    uint32_t getRecordtScore(void);

    vector<vector<uint8_t>> getIcon(void){
    	return this->game_icon;
    }

    void gameEnd();
    void gameBegin();
};


#endif /* INC_GAMES_GAME_HPP_ */
