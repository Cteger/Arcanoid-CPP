#include "Ball.h"
#include "Bonus.h"

#include <glut.h>

struct Ball BallInitialise(struct Racket racket)
{
	struct Ball ball;
	ball.size.height = BALL_SIZE_HEIGHT;
	ball.size.width = BALL_SIZE_WIDTH;
	ball.position.x = racket.position.x + racket.size.width / 2
		- ball.size.width / 2;
	ball.position.y = racket.position.y + ball.size.height;
	ball.launch_flag = 0;
	ball.vector.x = 0;
	ball.vector.y = SPEED;
	ball.max_speed = SPEED;

	ball.fire_ball_flag = 0;

	ball.color.red = 0;
	ball.color.green = 0;
	ball.color.blue = 0;

	return ball;
}

struct Window CheckBall(struct Window wind0)
{
	struct Window wind = wind0;

	int x0 = wind.ball[0].position.x + wind.ball[0].vector.x;
	int x1 = x0 + wind.ball[0].size.width;
	int y0 = wind.ball[0].position.y + wind.ball[0].vector.y;
	int y1 = y0 - wind.ball[0].size.height;

	if (x1 >= wind.size.width || x0 <= 0)
	{
		wind.ball[0].vector.x = (-1) * wind.ball[0].vector.x;
	}

	if (y0 >= wind.size.height - wind.menu_size)
	{
		wind.ball[0].vector.y = (-1) * wind.ball[0].vector.y;
		wind.ball = ReleaseFireBall(wind.ball);
	}

	if (y0 <= 0)
	{
		EndGame(0);
	}

	if ((x1 >= wind.racket.position.x)
		&& (x0 <= wind.racket.position.x + wind.racket.size.width)
		&& (y1 <= wind.racket.position.y))
	{
		wind.ball[0].vector.x += ((wind.racket.speed[0] - wind.racket.speed[1]) % 10);
		if (wind.ball[0].vector.x > wind.ball[0].max_speed)
		{
			wind.ball[0].vector.x = wind.ball[0].max_speed;
		}
		else if (wind.ball[0].vector.x < (-1) * wind.ball[0].max_speed)
		{
			wind.ball[0].vector.x = (-1) * wind.ball[0].max_speed;
		}
		wind.ball[0].vector.y = (-1) * wind.ball[0].vector.y;
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
			if (wind.ball[0].fire_ball_flag == 0)
			{
				wind.ball[0].vector.y = (-1) * wind.ball[0].vector.y;
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
			if (wind.ball[0].fire_ball_flag == 0)
			{
				wind.ball[0].vector.x = (-1) * wind.ball[0].vector.x;
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

	glColor3f(wind.ball[0].color.red,
		wind.ball[0].color.green,
		wind.ball[0].color.blue);

	for (int i = 0; i < wind.hp; i++)
	{
		glVertex2d(300 + i * wind.ball[0].size.width + i * 5,
			wind.size.height - 3);
		glVertex2d(300 + (i + 1) * wind.ball[0].size.width + 5 * i,
			wind.size.height - 3);
		glVertex2d(300 + (i + 1) * wind.ball[0].size.width + 5 * i,
			wind.size.height - 3 - wind.ball[0].size.height);
		glVertex2d(300 + i * (wind.ball[0].size.width + 5),
			wind.size.height - 3 - wind.ball[0].size.height);
	}
}

void DrawBall(struct Ball* ball)
{
	glBegin(GL_QUADS);

	glColor3f(ball[0].color.red,
		ball[0].color.green,
		ball[0].color.blue);

	glVertex2d(ball[0].position.x, ball[0].position.y);
	glVertex2d(ball[0].position.x + ball[0].size.width,
		ball[0].position.y);
	glVertex2d(ball[0].position.x + ball[0].size.width,
		ball[0].position.y - ball[0].size.height);
	glVertex2d(ball[0].position.x,
		ball[0].position.y - ball[0].size.height);
	glEnd();
}