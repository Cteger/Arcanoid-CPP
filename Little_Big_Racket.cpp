#include "Little_Big_Racket.h"
#include <glut.h>

struct Window Little_Racket(struct Window wind0)
{
	struct Window wind = wind0;

	
	wind.racket.size.width /= 2;

	wind.racket.color.red = 0;
	wind.racket.color.green = 0;
	wind.racket.color.blue = 1;

	return wind;
}

struct Window Big_Racket(struct Window wind0)
{
	struct Window wind = wind0;

	wind.racket.size.width *= 1.4;

	wind.racket.color.red = 1;
	wind.racket.color.green = 0;
	wind.racket.color.blue = 0;

	return wind;
}
