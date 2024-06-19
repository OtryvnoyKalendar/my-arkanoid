#include <stdio.h> //input output в консоль, изменение размера консоли
#include <stdlib.h> // операции с памятью
#include <math.h> // математика
#include <time.h> // время, остановка времени

#include "main.h"
#include "core.h"
#include "gameplay.h"
#include "tui.h"
#include "map.h"
#include "graphic.h"

int level = 1;
int run = 0;

tRocket rocket;
tBall ball;

// открытие/закрытие программы

void OpenConsoleMode() {
	setConsoleSize(ConsoleWidth, ConsoleHeight);
	setConsoleTitle("My Arkanoid! v.0.5");
	OpenNcursesMode();
}

void CloseConsoleMode() {
	CloseNcursesMode();
}

void BeforeCloseProgram() {
	CloseConsoleMode();
}

// ввод

void GameControl() {
	CheckSignals();
	
	int moveRight = 0;
	int moveLeft = 0;
	
	char c = getch();
	
	switch(c) {
		case 'd':
			moveRight = 1; break;
		case 'a':
			moveLeft = 1; break;
		case 'q':
			CloseProgram(); break;
		case 'w':
			if(!run)
				run = 1;
			else
				backToRocket();
			break;
		case 'r':
			level++;
			run = 0;
			break;
	}
	
	rocket.plan_x = rocket.x;
	rocket.plan_y = rocket.y;
	int horizontalMove = 1;
	int xMove = 0;
	char plan_obj;
	
	if (moveLeft) {
		rocket.plan_x = rocket.x-1;
		xMove = -horizontalMove;
	}
	else if (moveRight) {
		rocket.plan_x = rocket.x+rocket.size;
		xMove = horizontalMove;
	}
	
	plan_obj = SYMBOL_WALL;
	if (IsMapCellExists(rocket.plan_y, rocket.plan_x)) {
    	plan_obj = map[rocket.plan_y][rocket.plan_x];
	}
	
	void doMovePlan() {
		rocket.x += xMove;
	}
	
	if (plan_obj == SYMBOL_NOTHING) {
		doMovePlan();
	}
}

void InitWorld() {
	srand(time(NULL));
	rocketInit();
	initBall();
	level = 1;
}

int main() {
	OpenConsoleMode();
	InitWorld();
	
	while(1) {
		ClearMap();
		mapInit();
		
		GameLogic();
		
		ShowMap();
		ShowGameInfo();
		
		GameControl();
	}
	
	CloseProgram();
	return EXIT_SUCCESS;
}
