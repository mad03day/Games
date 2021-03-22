#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define Block_h
#ifdef Block_h

typedef struct
{
	long int x;
	long int y;
} Dot;

typedef struct
{
	int id;
	Dot* dots;
	bool colizion;
	Texture texture;
	Sprite sprite;
	int count;
} Block;

Block set_block(int id, bool colizion);
Block make_arr_dots(Block blk);
Block set_cord_by_index(Block blk, long x, long y, int index);
void reallocate_dots(Block blk, int new_count);
void delete_arr(Block blk);

#endif