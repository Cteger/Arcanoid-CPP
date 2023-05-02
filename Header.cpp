#include "Header.h"
#include "Bloks.h"
#include "Ball.h"
#include "Racket.h"
#include "Bonus.h"

#include <glut.h>
#include <math.h>
#include <windows.h>
#include <iostream>

struct Window wind;

void SystemOpen(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
}

void SystemInitialise(int hp, struct Blok* bloks, int blok_count, int level)
{
	wind.size.width = WINDOW_SIZEX;
	wind.size.height = WINDOW_SIZEY;
	wind.position.x = WINDOW_POSITIONX;
	wind.position.y = WINDOW_POSITIONY;
	wind.menu_size = MENU_SIZE;

	wind.level = level;
	wind.hp = hp;

	wind.racket = RacketInitialise(wind.size.width);

	wind.ball = new struct Ball;

	wind.ball[0] = BallInitialise(wind.racket);

	wind = Level(wind, bloks, blok_count, wind.level);

	wind.bonus_count = 0;

	wind.ball = ReleaseFireBall(wind.ball);

	SystemUpdate();
}

void SystemUpdate()
{
	glutInitWindowPosition(wind.position.x, wind.position.y);
	glutInitWindowSize(wind.size.width, wind.size.height);
	wind.glutNum = glutCreateWindow("ARCONOID");

	gluOrtho2D(0, wind.size.width, 0, wind.size.height);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutPassiveMotionFunc(MouseMove);
	glutMouseFunc(MouseButton);

	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);

	glutMainLoop();
}

void SystemRelease()
{
	std::cout << "END" << std::endl << wind.score << std::endl;
	exit(1);
}

void RenderScene()
{
	if (wind.ball[0].launch_flag == 0)
	{
		wind.ball[0] = BallInitialise(wind.racket);
	}
	else
	{
		wind = CheckBall(wind);
		wind.ball[0].position.x += wind.ball[0].vector.x;
		wind.ball[0].position.y += wind.ball[0].vector.y;
		Sleep(SLEEP);
	}

	for (int i = 0; i < wind.bonus_count; i++)
	{
		wind = CheckBonus(wind, i);

		if (wind.bonus_count != 0)
		{
			(wind.bonus + i)->position.y += (wind.bonus + i)->vector.y;
		}
	}

	Draw();
}

void Draw()
{
	// очистка буфера цвета и глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(1.0, 1.0, 1.0, 1.0);

	//MENU
	DrawHP(wind);

	//BLOKS
	DrawBloks(wind.bloks, wind.blok_count);

	//RACKET
	DrawRacket(wind.racket);

	//BONUS
	DrawBonus(wind.bonus, wind.bonus_count);

	//BALL	
	DrawBall(wind.ball);

	glutSwapBuffers();
}

void MouseMove(int x, int y)
{
	wind.racket.speed[1] = wind.racket.speed[0];
	wind.racket.speed[0] = x;

	wind.count++;

	if (x >= wind.size.width - wind.racket.size.width + wind.racket.size.width / 2)
	{
		wind.racket.position.x = wind.size.width - wind.racket.size.width;
	}
	else if (x <= wind.racket.size.width / 2)
	{
		wind.racket.position.x = 0;
	}
	else
	{
		wind.racket.position.x = x - wind.racket.size.width / 2;
	}

	glutPostRedisplay();
}

void MouseButton(int button, int state, int x, int y)
{
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) &&
		(wind.ball[0].launch_flag == 0))
	{
		wind.ball[0].vector.x = wind.racket.speed[0] - wind.racket.speed[1] + 1;
		wind.ball[0].vector.y = sqrt(wind.ball[0].max_speed * wind.ball[0].max_speed
			- wind.ball[0].vector.x * wind.ball[0].vector.x);
		wind.ball[0].launch_flag = 1;
		glutPostRedisplay();
	}
}

struct Window Destroy(struct Window wind0, int i)
{
	struct Window wind = wind0;

	if (wind.blok_count == 1)
	{
		EndGame(1);
	}
	else
	{
		if ((wind.bloks + i)->strength == 1 || wind.ball[0].fire_ball_flag == 1)
		{
			if (BONUS_CHANSE == 1)
			{
				wind.bonus_count++;
				wind.bonus = (struct Bonus*)realloc(wind.bonus, wind.bonus_count * sizeof(struct Bonus));
				wind.bonus[wind.bonus_count - 1] = BonusInitialise(wind.bloks[i]);
			}

			for (int j = i; j < wind.blok_count - 1; j++)
			{
				wind.bloks[j] = wind.bloks[j + 1];
			}

			wind.blok_count--;

			wind.bloks = (struct Blok*)realloc(wind.bloks,
				wind.blok_count * sizeof(struct Blok));

			wind.score += 20;
		}
		else
		{
			(wind.bloks + i)->strength--;
			wind.score += 30;
		}
	}
	return wind;
}

void EndGame(int win_point)
{
	if (win_point == 1)
	{
		if (wind.level == 2)
		{
			SystemRelease();
		}
		wind.level++;
		SystemInitialise(wind.hp, 0, 0, wind.level);
	}
	else
	{
		if (wind.hp == 1)
		{
			SystemRelease();
		}
		else
		{
			wind.hp--;
			SystemInitialise(wind.hp, wind.bloks, wind.blok_count, wind.level);
		}
	}
}