#pragma once
#include "Header.h"

void BonusInitialise(struct Bonus& bonus, struct Blok& blok);

void CheckBonus(struct Window& wind, int bonus_number);

void BonusDestroy(struct Bonus*& bonus0, int bonus_count, int bonus_number);

void BonusCatch(struct Window& wind, int bonus_number);

void DrawBonus(struct Bonus*& bonus, int bonus_count);

void FireBallInitialise(struct Ball*& ball);

void ReleaseFireBall(struct Ball*& ball);

void LittleRacketInitialise(struct Racket& racket);

void BigRacketInitialise(struct Racket& racket);

void NewHP(int& hp);