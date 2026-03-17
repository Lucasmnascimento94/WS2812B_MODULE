/*
 * MyRandom.hpp
 *
 *  Created on: Jan 16, 2026
 *      Author: lucasnascimento
 */

#ifndef INC_MYRANDOM_HPP_
#define INC_MYRANDOM_HPP_

#include <cstring>
#include <cstdint>
#include <vector>
#include <random>
#include <chrono>


class MyRandom {
	public:
	explicit MyRandom();
    	std::mt19937 engine;

    	void initRng();
    	int getRandom(int min, int max);
};



#endif /* INC_MYRANDOM_HPP_ */
