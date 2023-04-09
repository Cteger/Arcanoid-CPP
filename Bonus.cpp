#include "Bonus.h"
#include "Fire_Ball.h"
#include "Little_Big_Racket.h"
#include "New_HP.h"
#include <glut.h>
#include <stdlib.h>

struct Window BonusInitialise(struct Window wind0, int bonus_count, int blok_number)
{
	struct Window wind = wind0;
	bonus_count++;
	wind.bonus_count = bonus_count;
	//wind.bonus = new struct Bonus[bonus_count];
	wind.bonus = (struct Bonus*)realloc(wind.bonus, bonus_count * sizeof(struct Bonus));
	int i = bonus_count - 1;
	(wind.bonus + i)->size.height = BONUS_SIZE_HEIGHT;
	(wind.bonus + i)->size.width = BONUS_SIZE_WIDTH;
	(wind.bonus + i)->position.x = (wind.bloks + blok_number)->position.x + (wind.bloks->size.width) / 2
		- BONUS_SIZE_WIDTH / 2;
	(wind.bonus + i)->position.y = (wind.bloks + blok_number)->position.y - (wind.bloks->size.height) / 2
		+ BONUS_SIZE_HEIGHT / 2;
	(wind.bonus + i)->type = rand() % 4 + 1;

	if ((wind.bonus + i)->type == 1)
	{
		(wind.bonus + i)->color.red = 1.0;
		(wind.bonus + i)->color.green = 0.1;
		(wind.bonus + i)->color.blue = 0.1;
	}
	else if ((wind.bonus + i)->type == 2)
	{
		(wind.bonus + i)->color.red = 0.0;
		(wind.bonus + i)->color.green = 0.5;
		(wind.bonus + i)->color.blue = 1.0;
	}
	else if ((wind.bonus + i)->type == 3)
	{
		(wind.bonus + i)->color.red = 1.0;
		(wind.bonus + i)->color.green = 0.5;
		(wind.bonus + i)->color.blue = 0.0;
	}
	else if ((wind.bonus + i)->type == 4)
	{
		(wind.bonus + i)->color.red = 0.0;
		(wind.bonus + i)->color.green = 0.0;
		(wind.bonus + i)->color.blue = 0.0;
	}

	(wind.bonus + i)->vector.x = 0;
	(wind.bonus + i)->vector.y = (-0.5) * SPEED;

	return(wind);
}

struct Window CheckBonus(struct Window wind0, int bonus_number)
{
	struct Window wind = wind0;

	int x0 = (wind.bonus + bonus_number)->position.x;
	int x1 = x0 + (wind.bonus + bonus_number)->size.width;
	int y0 = (wind.bonus + bonus_number)->position.y + (wind.bonus + bonus_number)->vector.y;
	int y1 = y0 - (wind.bonus + bonus_number)->size.height;

	if (y0 <= 0)
	{
		wind = Bonus_destroy(wind, bonus_number);
	}
	else if ((x1 >= wind.racket.position.x)
		&& (x0 <= wind.racket.position.x + wind.racket.size.width)
		&& (y1 <= wind.racket.position.y))
	{
		wind = Bonus_catch(wind, bonus_number);
	}
	return wind;
}

struct Window Bonus_catch(struct Window wind0, int bonus_number)
{
	struct Window wind = wind0;

	wind.score += 100;

	if ((wind.bonus + bonus_number)->type == 1)
	{
		wind = Bonus_destroy(wind, bonus_number);

		wind = Fire_Ball(wind);
	}
	else if ((wind.bonus + bonus_number)->type == 2)
	{
		wind = Bonus_destroy(wind, bonus_number);

		wind = Little_Racket(wind);
	}
	else if ((wind.bonus + bonus_number)->type == 3)
	{
		wind = Bonus_destroy(wind, bonus_number);

		wind = Big_Racket(wind);
	}
	else if ((wind.bonus + bonus_number)->type == 4)
	{
		wind = Bonus_destroy(wind, bonus_number);

		wind = New_HP(wind);
	}

	return wind;
}

struct Window Bonus_destroy(struct Window wind0, int bonus_number)
{
	struct Window wind = wind0;

	for (int i = bonus_number; i < wind.bonus_count - 1; i++)
	{
		wind.bonus[i] = wind.bonus[i + 1]; // ÊÀÊ ÎÑÂÎÁÎÄÈÒÜ ÏÀÌßÒÜ?
	}

	//delete& wind.bonus[wind.bonus_count]; // Âðîäå òàê, íî íå òî÷íî
	wind.bonus_count--;

	wind.bonus = (struct Bonus*)realloc(wind.bonus, wind.bonus_count * sizeof(struct Bonus));

	return wind;
}

void DrawBonus(struct Window wind)
{
	glBegin(GL_QUADS);

	for (int i = 0; i < wind.bonus_count; i++)
	{
		glColor3f((wind.bonus + i)->color.red,
			(wind.bonus + i)->color.green,
			(wind.bonus + i)->color.blue);

		glVertex2d((wind.bonus + i)->position.x, (wind.bonus + i)->position.y);
		glVertex2d((wind.bonus + i)->position.x + (wind.bonus + i)->size.width,
			(wind.bonus + i)->position.y);
		glVertex2d((wind.bonus + i)->position.x + (wind.bonus + i)->size.width,
			(wind.bonus + i)->position.y - (wind.bonus + i)->size.height);
		glVertex2d((wind.bonus + i)->position.x,
			(wind.bonus + i)->position.y - (wind.bonus + i)->size.height);
	}
	glEnd();
}