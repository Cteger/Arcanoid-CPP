#pragma once
#define BALL_SIZE_HEIGHT 10
#define BALL_SIZE_WIDTH 10
#define WINDOW_POSITIONX 200
#define WINDOW_POSITIONY 50
#define WINDOW_SIZEX 400
#define WINDOW_SIZEY 600
#define RACKET_WIDTH 100
#define RACKET_HIGHT 7
#define BONUS_SIZE_HEIGHT 30
#define BONUS_SIZE_WIDTH 30
#define BLOK_COUNT1 15
#define MENU_SIZE 20
#define SLEEP 1
#define SPEED 7
#define BONUS_CHANSE (rand() % 4 + 1)

struct Color
{
	float red, green, blue;
};

struct Position
{
	int x;
	int y;
};

struct Size
{
	int height;
	int width;
};

struct Vector
{
	float x, y;
};

struct Blok
{
	struct Position position;
	struct Size size;

	int strength;
	struct Color color;
};

struct Racket
{
	struct Position position;
	struct Color color;
	struct Size size;
	int *speed;
};

struct Ball
{
	struct Size size;
	struct Position position;
	struct Color color;
	int launch;
	int fire_flag;
	struct Vector vector;
	int max_speed;
};

struct Bonus
{
	struct Size size;
	struct Position position;
	int type;
	struct Color color;
	struct Vector vector;
};

struct Window
{
	struct Size size;
	struct Position position;
	struct Color color;
	struct Blok* bloks;
	struct Ball ball;
	struct Racket racket;
	struct Bonus* bonus;
	float buffer[10];
	int count;
	int blok_count;
	int bonus_count;
	int glutNum;
	int hp;
	int level;
	int test;
	int menu_size;
	int score;
};

void SystemOpen(int argc, char** argv);

void SystemClose();

void SystemRelease();

void SystemInitialise(int hp, struct Blok* blok, int blok_count, int level);

void SystemUpdate();

void RenderScene();

void SecondScene();

void WindDisplay();

void Draw();

void MouseMove(int x, int y);

void MouseButton(int button, int state, int x, int y);

struct Window Destroy(struct Window wind0, int i);

void EndGame(int win_point);