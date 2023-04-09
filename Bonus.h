#pragma once
#include "Header.h"

struct Window BonusInitialise(struct Window wind0, int bonus_count, int i);

struct Window CheckBonus(struct Window wind0, int bonus_number);

struct Window Bonus_destroy(struct Window wind0, int bonus_number);

struct Window Bonus_catch(struct Window wind0, int bonus_number);

void DrawBonus(struct Window wind);