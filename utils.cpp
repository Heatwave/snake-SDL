#include "utils.h"

bool checkPosOverlap(Pos src, Pos dst)
{
	if (src.x == dst.x && src.y == dst.y)
	{
		return true;
	}
	return false;
}
