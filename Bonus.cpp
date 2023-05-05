#include "Bonus.h"

#include <glut.h>
#include <stdlib.h>

void BonusInitialise(struct Bonus& bonus, struct Blok& blok)
{
	bonus.size.height = BONUS_SIZE_HEIGHT;
	bonus.size.width = BONUS_SIZE_WIDTH;
	bonus.position.x = blok.position.x + (blok.size.width) / 2
		- BONUS_SIZE_WIDTH / 2;
	bonus.position.y = blok.position.y - (blok.size.height) / 2
		+ BONUS_SIZE_HEIGHT / 2;
	bonus.type = rand() % 4 + 1;

	if (bonus.type == 1)
	{
		bonus.color.red = 1.0;
		bonus.color.green = 0.1;
		bonus.color.blue = 0.1;
	}
	else if (bonus.type == 2)
	{
		bonus.color.red = 0.0;
		bonus.color.green = 0.5;
		bonus.color.blue = 1.0;
	}
	else if (bonus.type == 3)
	{
		bonus.color.red = 1.0;
		bonus.color.green = 0.5;
		bonus.color.blue = 0.0;
	}
	else if (bonus.type == 4)
	{
		bonus.color.red = 0.0;
		bonus.color.green = 0.0;
		bonus.color.blue = 0.0;
	}

	bonus.vector.x = 0;
	bonus.vector.y = (-0.5) * SPEED;
}

void CheckBonus(struct Window& wind, int bonus_number)
{
	int x0 = (wind.bonus + bonus_number)->position.x;
	int x1 = x0 + (wind.bonus + bonus_number)->size.width;
	int y0 = (wind.bonus + bonus_number)->position.y + (wind.bonus + bonus_number)->vector.y;
	int y1 = y0 - (wind.bonus + bonus_number)->size.height;

	if (y0 <= 0)
	{
		BonusDestroy(wind.bonus, wind.bonus_count, bonus_number);
		wind.bonus_count--;
	}
	else if ((x1 >= wind.racket.position.x)
		&& (x0 <= wind.racket.position.x + wind.racket.size.width)
		&& (y1 <= wind.racket.position.y))
	{
		BonusCatch(wind, bonus_number);
	}
}

void BonusCatch(struct Window& wind, int bonus_number)
{
	wind.score += 100;

	if ((wind.bonus + bonus_number)->type == 1)
	{
		BonusDestroy(wind.bonus, wind.bonus_count, bonus_number);
		wind.bonus_count--;

		FireBallInitialise(wind.ball);
	}
	else if ((wind.bonus + bonus_number)->type == 2)
	{
		BonusDestroy(wind.bonus, wind.bonus_count, bonus_number);
		wind.bonus_count--;

		LittleRacketInitialise(wind.racket);
	}
	else if ((wind.bonus + bonus_number)->type == 3)
	{
		BonusDestroy(wind.bonus, wind.bonus_count, bonus_number);
		wind.bonus_count--;

		BigRacketInitialise(wind.racket);
	}
	else if ((wind.bonus + bonus_number)->type == 4)
	{
		BonusDestroy(wind.bonus, wind.bonus_count, bonus_number);
		wind.bonus_count--;

		NewHP(wind.hp);
	}
}

void BonusDestroy(struct Bonus*& bonus, int bonus_count, int bonus_number)
{
	for (int i = bonus_number; i < bonus_count - 1; i++)
	{
		bonus[i] = bonus[i + 1];
	}

	bonus_count--;

	bonus = (struct Bonus*)realloc(bonus, bonus_count * sizeof(struct Bonus));
}

void DrawBonus(struct Bonus*& bonus, int bonus_count)
{
	glBegin(GL_QUADS);

	for (int i = 0; i < bonus_count; i++)
	{
		glColor3f((bonus + i)->color.red,
			(bonus + i)->color.green,
			(bonus + i)->color.blue);

		glVertex2d((bonus + i)->position.x, (bonus + i)->position.y);
		glVertex2d((bonus + i)->position.x + (bonus + i)->size.width,
			(bonus + i)->position.y);
		glVertex2d((bonus + i)->position.x + (bonus + i)->size.width,
			(bonus + i)->position.y - (bonus + i)->size.height);
		glVertex2d((bonus + i)->position.x,
			(bonus + i)->position.y - (bonus + i)->size.height);
	}
	glEnd();
}

void FireBallInitialise(struct Ball*& ball)
{
	ball[0].fire_ball_flag = 1;

	ball[0].color.red = 1;
	ball[0].color.green = 0.1;
	ball[0].color.blue = 0.1;
}

void ReleaseFireBall(struct Ball*& ball)
{
	ball[0].fire_ball_flag = 0;

	ball[0].color.red = 0.0;
	ball[0].color.green = 0.0;
	ball[0].color.blue = 0.0;
}

void LittleRacketInitialise(struct Racket& racket)
{
	racket.size.width /= 2;

	racket.color.red = 0;
	racket.color.green = 0;
	racket.color.blue = 1;
}

void BigRacketInitialise(struct Racket& racket)
{
	racket.size.width *= 1.4;

	racket.color.red = 1;
	racket.color.green = 0;
	racket.color.blue = 0;
}

void NewHP(int& hp)
{
	if (hp < 3)
	{
		hp++;
	}
}