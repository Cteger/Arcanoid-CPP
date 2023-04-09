#include "Ball.h"
#include "Fire_Ball.h"
#include <glut.h>

struct Ball BallInitialise(struct Window wind0)
{
	struct Window wind = wind0;
	wind.ball.size.height = BALL_SIZE_HEIGHT;
	wind.ball.size.width = BALL_SIZE_WIDTH;
	wind.ball.position.x = wind.racket.position.x + wind.racket.size.width / 2
		- wind.ball.size.width / 2;
	wind.ball.position.y = wind.racket.position.y + wind.ball.size.height;
	wind.ball.launch = 0;
	wind.ball.vector.x = 0;
	wind.ball.vector.y = SPEED;
	wind.ball.max_speed = SPEED;

	wind.ball.color.red = 0;
	wind.ball.color.green = 0;
	wind.ball.color.blue = 0;

	return wind.ball;
}

struct Window CheckBall(struct Window wind0)
{
	struct Window wind = wind0;

	int x0 = wind.ball.position.x + wind.ball.vector.x;
	int x1 = x0 + wind.ball.size.width;
	int y0 = wind.ball.position.y + wind.ball.vector.y;
	int y1 = y0 - wind.ball.size.height;

	if (x1 >= wind.size.width || x0 <= 0)
	{
		wind.ball.vector.x = (-1) * wind.ball.vector.x;
	}

	if (y0 >= wind.size.height - wind.menu_size)
	{
		wind.ball.vector.y = (-1) * wind.ball.vector.y;
		wind = Release_Fire_Ball(wind);
	}

	if (y0 <= 0)
	{
		EndGame(0);
	}

	if ((x1 >= wind.racket.position.x)
		&& (x0 <= wind.racket.position.x + wind.racket.size.width)
		&& (y1 <= wind.racket.position.y))
	{
		wind.ball.vector.x += ((wind.racket.speed[0] - wind.racket.speed[1]) % 10);
		if (wind.ball.vector.x > wind.ball.max_speed)
		{
			wind.ball.vector.x = wind.ball.max_speed;
		}
		else if (wind.ball.vector.x < (-1) * wind.ball.max_speed)
		{
			wind.ball.vector.x = (-1) * wind.ball.max_speed;
		}
		wind.ball.vector.y = (-1) * wind.ball.vector.y;
	}

	for (int i = 0; i < wind.blok_count; i++)
	{
		if ((x1 > (wind.bloks + i)->position.x)
			&& (x0 < (wind.bloks + i)->position.x + (wind.bloks + i)->size.width)
			&& (y1 < (wind.bloks + i)->position.y)
			&& (y0 > (wind.bloks + i)->position.y)
			&& (y0 > (wind.bloks + i)->position.y - (wind.bloks + i)->size.height)
			|| ((x1 > (wind.bloks + i)->position.x)
			&& (x0 < (wind.bloks + i)->position.x + (wind.bloks + i)->size.width)
			&& (y1 < (wind.bloks + i)->position.y - (wind.bloks + i)->size.height)
			&& (y0 > (wind.bloks + i)->position.y - (wind.bloks + i)->size.height)))
		{
			if (wind.ball.fire_flag == 0)
			{
				wind.ball.vector.y = (-1) * wind.ball.vector.y;
			}
			wind = Destroy(wind, i);
			break;
		}
		else if ((x1 > (wind.bloks + i)->position.x)
			&& (x0 < (wind.bloks + i)->position.x + (wind.bloks + i)->size.width)
			&& (x0 < (wind.bloks + i)->position.x)
			&& (y1 < (wind.bloks + i)->position.y)
			&& (y0 > (wind.bloks + i)->position.y - (wind.bloks + i)->size.height)
			|| (x1 > (wind.bloks + i)->position.x)
			&& (x1 > (wind.bloks + i)->position.x + (wind.bloks + i)->size.width)
			&& (x0 < (wind.bloks + i)->position.x + (wind.bloks + i)->size.width)
			&& (y1 < (wind.bloks + i)->position.y)
			&& (y0 > (wind.bloks + i)->position.y - (wind.bloks + i)->size.height))
		{
			if (wind.ball.fire_flag == 0)
			{
				wind.ball.vector.x = (-1) * wind.ball.vector.x;
			}
			wind = Destroy(wind, i);
			break;
		}
	}

	return wind;
}

void DrawHP(struct Window wind)
{
	glColor3f(0, 0, 0);

	glBegin(GL_LINE_LOOP);

	glVertex2d(0, wind.size.height - 1);
	glVertex2d(wind.size.width, wind.size.height - 1);
	glVertex2d(wind.size.width, wind.size.height - wind.menu_size);
	glVertex2d(0, wind.size.height - wind.menu_size);

	glEnd();


	glBegin(GL_QUADS);

	glColor3f(wind.ball.color.red,
		wind.ball.color.green,
		wind.ball.color.blue);

	for (int i = 0; i < wind.hp; i++)
	{
		glVertex2d(300 + i * wind.ball.size.width + i * 5,
			wind.size.height - 3);
		glVertex2d(300 + (i + 1) * wind.ball.size.width + 5 * i,
			wind.size.height - 3);
		glVertex2d(300 + (i + 1) * wind.ball.size.width + 5 * i,
			wind.size.height - 3 - wind.ball.size.height);
		glVertex2d(300 + i * (wind.ball.size.width + 5),
			wind.size.height - 3 - wind.ball.size.height);
	}
}

void DrawBall(struct Window wind)
{
	glBegin(GL_QUADS);

	glColor3f(wind.ball.color.red,
		wind.ball.color.green,
		wind.ball.color.blue);

	glVertex2d(wind.ball.position.x, wind.ball.position.y);
	glVertex2d(wind.ball.position.x + wind.ball.size.width,
		wind.ball.position.y);
	glVertex2d(wind.ball.position.x + wind.ball.size.width,
		wind.ball.position.y - wind.ball.size.height);
	glVertex2d(wind.ball.position.x,
		wind.ball.position.y - wind.ball.size.height);
	glEnd();
}