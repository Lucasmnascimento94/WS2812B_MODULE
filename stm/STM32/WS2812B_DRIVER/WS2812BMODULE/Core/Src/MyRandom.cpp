/*
 * MyRandom.cpp
 *
 *  Created on: Jan 16, 2026
 *      Author: lucasnascimento
 */



#include "MyRandom.hpp"
#include "timers.h"

MyRandom::MyRandom()
{

}

void MyRandom::initRng() {
  uint32_t seed = (uint32_t)HAL_GetTick() ^ (uint32_t)TIM2->CNT; // pick a running timer
  this->engine.seed(seed);
}

int MyRandom::getRandom(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max); // inclusive in both ends
	return (uint8_t)dist(this->engine);
}
