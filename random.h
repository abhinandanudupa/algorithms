#pragma once


#include <stdlib.h>


int get_random_int(int min, int max)
{
	return min + (rand() % (max - min + 1));
}
