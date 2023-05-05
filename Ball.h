#pragma once
#include "Header.h"

void BallInitialise(struct Ball& ball, struct Racket& racket);

void CheckBall(struct Window& wind);

void DrawHP(struct Window& wind);

void DrawBall(struct Ball*& ball);