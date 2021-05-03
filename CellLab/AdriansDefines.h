#pragma once

#define WINDOWX 1800
#define WINDOWY 1000

#define XY(v) (v).x,(v).y

#define asRadians(degrees) degrees * 0.0174533

#define getrandom(min, max) ((rand()%(int)(((max) + 1) - (min)))+ (min))


#define FOOD_MAX_SPAWN 2000
#define FOOD_START_FOOD 2.f
#define FOOD_STARD_RADIUS 0.01f
#define FOOD_GROWTH_RATE 1.3f
#define FOOD_MAX_SIZE 3.f

#define CELL_PUSHBACK 2.f