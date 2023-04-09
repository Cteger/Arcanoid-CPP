#include "Racket.h"
#include <glut.h>

struct Racket RacketInitialise(struct Window wind0)
{
	struct Window wind = wind0;
	wind.racket.size.height = RACKET_HIGHT;
	wind.racket.size.width = RACKET_WIDTH;
	wind.racket.position.x = wind.size.width / 2;
	wind.racket.position.x = (wind.size.width - RACKET_WIDTH) / 2;
	wind.racket.position.y = 10;

	wind.racket.color.red = 0;
	wind.racket.color.green = 1;
	wind.racket.color.blue = 0;
	
	wind.racket.speed = new int[2];

	return wind.racket;
}

void DrawRacket(struct Window wind)
{
	glBegin(GL_QUADS);

	glColor3f(wind.racket.color.red,
			  wind.racket.color.green,
			  wind.racket.color.blue);

	glVertex2d(wind.racket.position.x, wind.racket.position.y);
	glVertex2d(wind.racket.position.x + wind.racket.size.width,
		wind.racket.position.y);
	glVertex2d(wind.racket.position.x + wind.racket.size.width,
		wind.racket.position.y - wind.racket.size.height);
	glVertex2d(wind.racket.position.x,
		wind.racket.position.y - wind.racket.size.height);

	glEnd();
}