#include "utils.h"

bool checkPosOverlap(Pos src, Pos dst)
{
	if (src.x == dst.x && src.y == dst.y)
	{
		return true;
	}
	return false;
}

int floorInt(int num, int base)
{
	int modNum = num % base;
	if (modNum == 0)
	{
		return num;
	}
	return num - modNum;
}
