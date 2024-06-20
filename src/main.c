#include <time.h> // для time()

#include "main.h"
#include "core.h"
#include "gameplay.h"
#include "tui.h"
#include "map.h"
#include "graphic.h"
#include "keys.h"

#define GAME_DELAY_CONSTANT 50

int level = 1;
int run = 0;

tRocket rocket;
tBall ball;

// открытие/закрытие программы

void OpenConsoleMode() {
	setConsoleSize(ConsoleWidth, ConsoleHeight);
	setConsoleTitle("My Arkanoid! v.1.0");
	OpenNcursesMode();
	OpenKeysMode();
}

void CloseConsoleMode() {
	CloseNcursesMode();
	CloseKeysMode();
}

void BeforeCloseProgram() {
	CloseConsoleMode();
}

// ввод

void GameControl() {
	CheckSignals();
	RefreshKeyboardStatus();
	
	int moveRight = 0;
	int moveLeft = 0;
	
	if(GetKeyState(KEY_D)) {
		moveRight = 1;
	}
	if(GetKeyState(KEY_A)) {
		moveLeft = 1;
	}
	if(GetKeyState(KEY_SPACE)) {
		racketShoot();
	}
	else if(GetKeyState(KEY_ESC)) {
		CloseProgram();
	}
	else if(GetKeyState(KEY_R)) {
		GoToNextLevel();
	}
	else if(GetKeyPressed(KEY_W)) {
		if(!run)
			run = 1;
		//else
			//backToRocket();
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
	lvlMapInit();
}

int main() {
	OpenConsoleMode();
	InitWorld();
	
	while(1) {
		ClearMap();
		lvlMapPut();
		
		GameLogic();
		
		ShowMap();
		ShowGameInfo();
		
		GameControl();
		napms(GAME_DELAY_CONSTANT);
		GameControl();
	}
	
	CloseProgram();
	return EXIT_SUCCESS;
}
