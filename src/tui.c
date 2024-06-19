#include "core.h"
#include "map.h"
#include "main.h"
#include "graphic.h"
#include "gameplay.h"
#include <unistd.h> // для sleep()

#define bufSize 60

void ShowMap() {
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++) {
			char symbol = map[i][j];
			int color = COLOR_STANDARD;
			
			switch(symbol) {
				case SYMBOL_WALL:
					color = COLOR_WALL; break;
				case SYMBOL_ROCKET:
					color = COLOR_ROCKET; break;
				case SYMBOL_BALL:
					color = COLOR_BALL; break;
				case SYMBOL_GRID:
					color = COLOR_GRID; break;
				case SYMBOL_BRICK:
					color = COLOR_BRICK; break;
				case SYMBOL_WIDE:
					color = COLOR_WIDE; break;
				case SYMBOL_THIN:
					color = COLOR_THIN; break;
				case SYMBOL_BULLET:
					color = COLOR_BULLET; break;
			}
			
			PutSymbolToConsole(i, j, symbol, color);
		}
	refresh();
}

void ClearConsole() {
	for(int i=0; i<ConsoleHeight; i++)
		for(int j=0; j<ConsoleWidth; j++)
			DrawSymbolInConsole(i, j, SYMBOL_NOTHING, -1);
}

void ShowLevelPreview() {
	ClearMap();
	ClearConsole();
	
	char buf[bufSize];
	snprintf(buf, bufSize, "\t\t\t\t\t\t NEXT LEVEL");
	PutText(buf, 30, 0, COLOR_YELLOW);
	
	ShowMap();
	sleep(3);
	
	ClearConsole();
}

void ShowGameInfo() {
	int xstart = 80;
	char buf[bufSize];
	
	snprintf(buf, bufSize, "LEVEL     %d", level);
	PutText(buf, 5, xstart, COLOR_YELLOW);
	
	snprintf(buf, bufSize, "HIT   \t%4d", hitCnt);
	PutText(buf, 6, xstart, COLOR_YELLOW);
	
	snprintf(buf, bufSize, "RECORD %4d", hitCntMax);
	PutText(buf, 7, xstart, COLOR_YELLOW);
	
	snprintf(buf, bufSize, "racket.x = %3d", rocket.x);
	PutText(buf, 9, xstart, COLOR_YELLOW);
}
