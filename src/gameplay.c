#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "gameplay.h"
#include "map.h"
#include "main.h"
#include "tui.h"

int hitCnt = 0;
int hitCntNeed = 3;
int hitCntMax = 0;

void rocketInit() {
	rocket.size = 8;
	rocket.x = (width - rocket.size) / 2;
	rocket.y = height - 2;
	
	rocket.plan_x = rocket.x;
	rocket.plan_y = rocket.y;
}

void rocketPut() {
	for(int i=0; i<rocket.size; i++)
		map[rocket.y][rocket.x+i] = SYMBOL_ROCKET;
}

void backToRocket() {
	if (hitCnt > hitCntMax)
		hitCntMax = hitCnt;
	if (hitCnt >= hitCntNeed) {
		level++;
		ShowLevelPreview();
	}
	hitCnt = 0;
	
	run = 0;
	ball.alfa = (( (rand() % 20) / 19.0 ) - 2.0)*1.25;
}

void moveBall(float x, float y) {
	ball.x = x;
	ball.y = y;
	
	ball.ix = (int)round(ball.x);
	ball.iy = (int)round(ball.y);
}

void initBall() {
	moveBall(2, 2);
	ball.alfa = -M_PI/2;
	ball.speed = 0.0007;
}

void putBall() {
	if (IsMapCellExists(ball.iy, ball.ix))
		map[ball.iy][ball.ix] = SYMBOL_BALL;
}

void autoMoveBall() {
	if(ball.alfa < 0) ball.alfa += M_PI*2;
	else if (ball.alfa > M_PI*2) ball.alfa -= M_PI*2;
	
	tBall ballPrevious = ball;
	
	moveBall(ball.x + cos(ball.alfa) * ball.speed
			,ball.y + sin(ball.alfa) * ball.speed);
	
	if(map[ball.iy][ball.ix] == SYMBOL_WALL || map[ball.iy][ball.ix] == SYMBOL_ROCKET) {
		if(ball.ix != ballPrevious.ix && ball.iy != ballPrevious.iy) {
			if (map[ballPrevious.iy][ball.ix] == map[ball.iy][ballPrevious.ix])
				ballPrevious.alfa += M_PI;
			else {
				if (map[ballPrevious.iy][ball.ix] == SYMBOL_WALL)
					ballPrevious.alfa = (2*M_PI - ballPrevious.alfa) + M_PI;
				else
					ballPrevious.alfa = (2*M_PI - ballPrevious.alfa);
			}
		}
		else if (ball.iy == ballPrevious.iy)
			ballPrevious.alfa = (2*M_PI - ballPrevious.alfa) + M_PI;
		else
			ballPrevious.alfa = (2*M_PI - ballPrevious.alfa);
		
		if (map[ball.iy][ball.ix] == SYMBOL_ROCKET) {
			hitCnt++;
		}
		//printf("\a");
		ballPrevious.alfa += rand() % 20 / 19.0 / 3.0;
		ball = ballPrevious;
		autoMoveBall();
	}
	else if (map[ball.iy][ball.ix] == '=') {
		backToRocket();
	}
}

void GameLogic() {
	rocketPut();
	putBall();
	
	if(!run)
		moveBall(rocket.x + rocket.size/2, rocket.y-1);
	else
		autoMoveBall();
}
