#pragma once
#include "Header.h"

struct Bonus BonusInitialise(struct Blok blok);

struct Window CheckBonus(struct Window wind0, int bonus_number);

struct Bonus* BonusDestroy(struct Bonus* bonus0, int bonus_count, int bonus_number);

struct Window BonusCatch(struct Window wind0, int bonus_number);

void DrawBonus(struct Bonus* bonus, int bonus_count);

struct Ball* FireBallInitialise(struct Ball* ball0);

struct Ball* ReleaseFireBall(struct Ball* ball0);

struct Racket LittleRacketInitialise(struct Racket racket0);

struct Racket BigRacketInitialise(struct Racket racket0);

int NewHP(int hp);