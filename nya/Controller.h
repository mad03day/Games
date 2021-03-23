#pragma once
#include "player.h"
#include "Map.h"

#define Controller_h
#ifdef Controller_h

class Controller
{
public:
	player Personazh;
	Controller();
	~Controller();
	
private:
	void check_colision(player* pers, Map* blocks);
};

#endif // Controller_h
