/*
 * memory.cpp
 *
 *  Created on: Dec 25, 2025
 *      Author: lucasnascimento
 */

#include "print.hpp"
#include "memory.hpp"
#include <cstddef>

Pool::Pool(){
	this->top = 0;
	this->bot = 0;
	this->size = 0;
	for(uint32_t i = 0; i<MAX; i++){
		this->pool[i].next = NULL;
	}
}


uint8_t Pool::push(uint8_t i, uint8_t j){
	uint32_t tindex = this->top;
	uint32_t bindex = this->bot;
	uint32_t pindex = tindex + 1;

	if(pindex == MAX) pindex = 0;
	if(pindex == bindex) return MAXOUT;

	this->pool[tindex].next = &this->pool[pindex];

	this->pool[pindex].i = i;
	this->pool[pindex].j = j;
	this->top = pindex;
	this->size++;

	if(this->size == 1) {this->bot = this->top;}
	return NO_ERR;
}

uint8_t Pool::pop(){
	if(this->size ==0) return EMPTY_LIST;
	uint32_t bindex = this->bot;
	uint32_t pindex = bindex + 1;
	if(pindex == MAX) pindex = 0;
	this->pool[bindex].next = NULL;
	this->bot = pindex;
	this->size--;

	return NO_ERR;
}
