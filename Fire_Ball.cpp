#include "Fire_Ball.h"
#include <glut.h>

struct Window Fire_Ball(struct Window wind0)
{
	struct Window wind = wind0;

	wind.ball.fire_flag = 1;

	wind.ball.color.red = 1;
	wind.ball.color.green = 0.1;
	wind.ball.color.blue = 0.1;

	return wind;
}

struct Window Release_Fire_Ball(struct Window wind0)
{
	struct Window wind = wind0;

	wind.ball.fire_flag = 0;

	wind.ball.color.red = 0.0;
	wind.ball.color.green = 0.0;
	wind.ball.color.blue = 0.0;

	return wind;
}