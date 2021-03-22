#include "Block.h"

Block set_block(int id, bool colizion)
{
	Block blk;// = (Block*)malloc(sizeof(Block));
	blk.id = id;
	blk.colizion = colizion;
	return blk;
}

Block make_arr_dots(Block blk)
{
	blk.dots = (Dot*)malloc(sizeof(Dot) * blk.count);
	return blk;	
}
Block set_cord_by_index(Block blk, long x, long y, int index)
{
	if (index >= blk.count)
	{
		reallocate_dots(blk, index);
	}
	blk.dots[index].x = x;
	blk.dots[index].y = y;
	return blk;
}

void reallocate_dots(Block blk, int new_count)
{
	if (blk.count >= new_count)
		return;
	Dot* buffer = (Dot*)malloc(sizeof(Dot) * new_count);
	memcpy(buffer, blk.dots, new_count);
	free(blk.dots);
	blk.dots = buffer;
	blk.count = new_count;
	return;
}

void delete_arr(Block blk)
{
	free(blk.dots);
}