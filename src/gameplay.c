#include <math.h> // для M_PI

#include "gameplay.h"
#include "map.h"
#include "main.h"
#include "tui.h"
#include "core.h"
#include "object.h"

#define objBulletSpeed 		0.8f
#define objBallSpeed 		0.8f

int hitCnt = 0;
int hitCntNeed = 10;
int hitCntMax = 0;

void rocketInit() {
	rocket.size = 8;
	rocket.x = (width - rocket.size) / 2;
	rocket.y = height - 2;
	rocket.fireMode = 0;
	
	rocket.plan_x = rocket.x;
	rocket.plan_y = rocket.y;
}

void rocketPut() {
	for(int i=0; i<rocket.size; i++)
		map[rocket.y][rocket.x+i] = SYMBOL_ROCKET;
	if(rocket.fireMode > 0)
		map[rocket.y-1][rocket.x + rocket.size/2] = map[rocket.y-2][rocket.x + rocket.size/2] = SYMBOL_GUN;
}

void GoToNextLevel() {
	level++;
	run = 0;
	ShowLevelPreview();
	lvlMapInit();
	ObjArr_Clear();
	rocket.fireMode = 0;
}

void CheckWin() {	
	if(lvlMapBrickCount() == 0) // hitCnt >= hitCntNeed
		GoToNextLevel();
}

void backToRocket() {
	if(hitCnt > hitCntMax)
		hitCntMax = hitCnt;
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
	ball.speed = objBallSpeed;
}

void putBall() {
	if (IsMapCellExists(ball.iy, ball.ix))
		map[ball.iy][ball.ix] = SYMBOL_BALL;
}

void racketShoot() {
	if(rocket.fireMode != 1)
		return;
	
	ObjArr_Add(ObjCreate(rocket.x + rocket.size/2, rocket.y - 2, 
						-M_PI_2, objBulletSpeed, SYMBOL_BULLET
						));
	rocket.fireMode += 3;
}

void CountFireMode() {
	if(!run)
		rocket.fireMode = 0;
	
	if(rocket.fireMode > 1)
		rocket.fireMode--;
}

void autoMoveBall() {
	if(ball.alfa < 0) ball.alfa += M_PI*2;
	else if (ball.alfa > M_PI*2) ball.alfa -= M_PI*2;
	
	tBall ballPrevious = ball;
	
	moveBall(ball.x + cos(ball.alfa) * ball.speed
			,ball.y + sin(ball.alfa) * ball.speed);
	
	if(
	map[ball.iy][ball.ix] == SYMBOL_WALL
	|| map[ball.iy][ball.ix] == SYMBOL_ROCKET
	|| map[ball.iy][ball.ix] == SYMBOL_BRICK
	) {
		if (map[ball.iy][ball.ix] == SYMBOL_ROCKET) {
			hitCnt++;
			float pos = ball.x - rocket.x;
			float psi = pos / rocket.size * 2 - 1;
			psi *= M_PI_2 * 0.9f;
			if( !(psi < M_PI_2 && psi > -M_PI_2) ) {
				run = 0;
				return;
				//ErrorCloseProgram("неправильный расчёт угла");
			}
			ballPrevious.alfa = -M_PI_2 + psi;
		}
		else if(ball.ix != ballPrevious.ix && ball.iy != ballPrevious.iy) {
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
		
		ObjHitBrick(ball);
		
		//printf("\a");
		ballPrevious.alfa += rand() % 20 / 19.0 / 3.0;
		ball = ballPrevious;
		autoMoveBall();
	}
	else if (map[ball.iy][ball.ix] == SYMBOL_GRID) {
		backToRocket();
	}
}

void GameLogic() {
	rocketPut();
	ObjArr_Work();
	ObjArr_Put();
	
	if(!run)
		moveBall(rocket.x + rocket.size/2, rocket.y-1);
	else
		autoMoveBall();
	
	putBall();
	
	CheckWin();
	CountFireMode();
}
