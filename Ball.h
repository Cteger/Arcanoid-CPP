#pragma once
#include "Header.h"

struct Ball BallInitialise(struct Racket racket);

struct Window CheckBall(struct Window wind0);

void DrawHP(struct Window wind);

void DrawBall(struct Ball* ball);