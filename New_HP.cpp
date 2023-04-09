#include "New_HP.h"
#include <glut.h>

struct Window New_HP(struct Window wind0)
{
	struct Window wind = wind0;

	if (wind.hp < 3)
	{
		wind.hp++;
	}

	return wind;
}