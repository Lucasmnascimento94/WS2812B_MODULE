/*
 * Game.cpp
 *
 *  Created on: Nov 28, 2025
 *      Author: lucasnascimento
 */

#include <cstdint>
#include "Game.hpp"
#include "Records.hpp"

Game::Game(std::string name)
	:game_name(name)
{
	// Read current game's Record Score from flash
	// Read Game Icon from flash and write it to Shared Memory
	for(int i=0; i<96; i++){
		for(int j=0; j<96; j++){
			this->map[i][j] = VOID;
		}
	}
}


/******************************************************************************/
/*                        			SETTERS     		   	                  */
/******************************************************************************/


// -----------------------------------------------------------------------------
// @brief  Set current Score in the game
// -----------------------------------------------------------------------------
void Game::setCurrentScore(uint32_t score){
    this->current_score = score;
    if (score > this->record_score) {
        setRecordScore(score);
        if (!this->newRecord) this->newRecord = true;
    }
}

// -----------------------------------------------------------------------------
// @brief  Set record score
// @param  score   New high score value
// -----------------------------------------------------------------------------
void Game::setRecordScore(uint32_t score) {
    this->record_score = score;
}

// -----------------------------------------------------------------------------
// @brief  Set player name with the highest achieved score
// @param  player name
// -----------------------------------------------------------------------------


void Game::initRng() {
  uint32_t seed = (uint32_t)HAL_GetTick() ^ (uint32_t)TIM2->CNT; // pick a running timer
  this->engine.seed(seed);
}

/******************************************************************************/
/*                        			GETTERS      		   	                  */
/******************************************************************************/

uint32_t Game::getCurrentScore(){
	return this->current_score;
}

uint32_t Game::getRecordScore(void){
	return this->record_score;
}


// -----------------------------------------------------------------------------
// @brief  Terminate the game
// @param
// -----------------------------------------------------------------------------
void Game::gameEnd() {
    // TODO
}

// -----------------------------------------------------------------------------
// @brief  Initialize the game
// @param
// -----------------------------------------------------------------------------
void Game::gameBegin() {
    // TODO
}
