/*
 * Event.hpp
 *
 *  Created on: Jan 26, 2026
 *      Author: lucasnascimento
 */

#ifndef INC_EVENT_EVENT_HPP_
#define INC_EVENT_EVENT_HPP_

#pragma once
class Game;

class Event {
public:
	Game *game;

	explicit Event();
};


#endif /* INC_EVENT_EVENT_HPP_ */

class SnakeEvent : public Event{
public:
	explicit SnakeEvent();
};

class PongGameEvent : public Event{
public:
	explicit PongGameEvent();
};



class SpaceGameEvent : public Event{
public:
	explicit SpaceGameEvent();
};
