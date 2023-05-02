#include "Racket.h"
#include <glut.h>

struct Racket RacketInitialise(int width)
{
	struct Racket racket;
	racket.size.height = RACKET_HIGHT;
	racket.size.width = RACKET_WIDTH;
	racket.position.x = width / 2;
	racket.position.x = (width - RACKET_WIDTH) / 2;
	racket.position.y = 10;

	racket.color.red = 0;
	racket.color.green = 1;
	racket.color.blue = 0;
	
	racket.speed = new int[2];

	return racket;
}

void DrawRacket(struct Racket racket)
{
	glBegin(GL_QUADS);

	glColor3f(racket.color.red,
			  racket.color.green,
			  racket.color.blue);

	glVertex2d(racket.position.x, racket.position.y);
	glVertex2d(racket.position.x + racket.size.width,
		racket.position.y);
	glVertex2d(racket.position.x + racket.size.width,
		racket.position.y - racket.size.height);
	glVertex2d(racket.position.x,
		racket.position.y - racket.size.height);

	glEnd();
}