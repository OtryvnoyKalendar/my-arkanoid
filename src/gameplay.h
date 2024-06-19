#pragma once

typedef struct {
	int x, y;
	int size;
	
	int plan_x;
	int plan_y;
	char plan_obj;
} tRocket;

typedef struct {
	float x, y;
	int ix, iy;
	float alfa;
	float speed;
} tBall;

extern tRocket rocket;
extern tBall ball;

extern int hitCnt;
extern int hitCntNeed;
extern int hitCntMax;

void rocketInit();
void GameLogic();
void initBall();
void backToRocket();
