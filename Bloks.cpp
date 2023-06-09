#include "Bloks.h"
#include "Bonus.h"

#include <glut.h>
#include <stdlib.h>

void Level(struct Window& wind, int blok_count, int level)
{
	if (level == 1)
	{
		wind.blok_count = BLOK_COUNT1;
		wind.bloks = 0;
		wind.bloks = new struct Blok[wind.blok_count];
		for (int i = 0; i < wind.blok_count; i++)
		{
			(wind.bloks + i)->size.height = 60;
			(wind.bloks + i)->size.width = wind.size.width / 5;

			(wind.bloks + i)->strength = 1;
			(wind.bloks + i)->position.x = (i % 5) * (wind.bloks + i)->size.width;
		}

		for (int i = 0; i < wind.blok_count; i++)
		{
			if (i / 5 == 0)
			{
				(wind.bloks + i)->position.y = wind.size.height - wind.menu_size;
			}
			else if (i / 5 == 1)
			{
				(wind.bloks + i)->position.y = wind.bloks->position.y
					- (wind.bloks + i)->size.height;
			}
			else
			{
				(wind.bloks + i)->position.y = wind.bloks->position.y
					- 2 * (wind.bloks + i)->size.height;
			}
		}
	}
	else if (level == 2)
	{
		wind.blok_count = 120;
		wind.bloks = 0;
		wind.bloks = new struct Blok[wind.blok_count];
		for (int i = 0; i < wind.blok_count; i++)
		{
			(wind.bloks + i)->size.height = 15;
			(wind.bloks + i)->size.width = wind.size.width / 10;

			(wind.bloks + i)->strength = rand() % 4 + 1;
			(wind.bloks + i)->position.x = (i % 10) * (wind.bloks + i)->size.width;
		}

		for (int i = 0; i < wind.blok_count; i++)
		{
			if (i / 10 == 0)
			{
				(wind.bloks + i)->position.y = wind.size.height - wind.menu_size;
			}
			else
			{
				(wind.bloks + i)->position.y = wind.bloks->position.y
					- (i / 10) * (wind.bloks + i)->size.height;
			}
		}
	}
}

void DrawBloks(struct Blok*& bloks, int blok_count)
{
	glBegin(GL_QUADS);

	for (int i = 0; i < blok_count; i++)
	{
		if ((bloks + i)->strength == 1)
		{
			(bloks + i)->color.red = 0;
			(bloks + i)->color.green = 1.0;
			(bloks + i)->color.blue = 0.0;
		}
		else if ((bloks + i)->strength == 2)
		{
			(bloks + i)->color.red = 1.0;
			(bloks + i)->color.green = 1.0;
			(bloks + i)->color.blue = 0.0;
		}
		else if ((bloks + i)->strength == 3)
		{
			(bloks + i)->color.red = 0.1;
			(bloks + i)->color.green = 0.2;
			(bloks + i)->color.blue = 0.8;
		}
		else if ((bloks + i)->strength == 4)
		{
			(bloks + i)->color.red = 1.0;
			(bloks + i)->color.green = 0.5;
			(bloks + i)->color.blue = 0.5;
		}

		glColor3f((bloks + i)->color.red,
			(bloks + i)->color.green,
			(bloks + i)->color.blue);

		glVertex2d((bloks + i)->position.x, (bloks + i)->position.y);
		glVertex2d((bloks + i)->position.x + (bloks + i)->size.width,
			(bloks + i)->position.y);
		glVertex2d((bloks + i)->position.x + (bloks + i)->size.width,
			(bloks + i)->position.y - (bloks + i)->size.height);
		glVertex2d((bloks + i)->position.x,
			(bloks + i)->position.y - (bloks + i)->size.height);
	}

	glEnd();

	for (int i = 0; i < blok_count; i++)
	{
		glColor3f(0, 0, 0);

		glBegin(GL_LINE_LOOP);

		glVertex2d((bloks + i)->position.x, (bloks + i)->position.y);
		glVertex2d((bloks + i)->position.x + (bloks + i)->size.width,
			(bloks + i)->position.y);
		glVertex2d((bloks + i)->position.x + (bloks + i)->size.width,
			(bloks + i)->position.y - (bloks + i)->size.height);
		glVertex2d((bloks + i)->position.x,
			(bloks + i)->position.y - (bloks + i)->size.height);

		glEnd();
	}
}