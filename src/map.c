#include <string.h>

#include "map.h"
#include "main.h"

char map[height][width+1];
char lvlMap[height][width];

int IsMapCellExists(int mapY, int mapX) {
	return (mapY >= 0 && mapY < height && mapX >= 0 && mapX < width);
}

int IsConsoleCellExists(int mapY, int mapX) {
	return (mapY >= 0 && mapY < ConsoleHeight && mapX >= 0 && mapX < ConsoleWidth);
}

void putBarrierLine(int line, int xStart, int xEnd) {
	if (xStart<xEnd)
		for(int i=xStart; i<xEnd;i++)
			lvlMap[line][i] = SYMBOL_WALL;
}

void putBarrierVert(int line, int yStart, int yEnd) {
	if (yStart<yEnd)
		for(int i=yStart; i<yEnd;i++)
			lvlMap[i][line] = SYMBOL_WALL;
}

void lvlMapPuzzle() {
	switch(level) {
		case 1:
			putBarrierLine(7, 25, 40);
			putBarrierVert(25,4,8);
			putBarrierVert(40,4,8);
			break;
		case 2:
			putBarrierLine(10, 20, 45);
			putBarrierVert(18,7,15);
			putBarrierVert(46,7,15);
			break;
		case 3:
			putBarrierLine(10, 5, 10);
			putBarrierLine(10, 15, 20);		
			putBarrierLine(10, 25, 30);
			putBarrierLine(10, 35, 40);
			
			putBarrierLine(15, 30, 40);
			putBarrierLine(15, 42, 60);
			break;
		case 4:
			putBarrierLine(5, 25, 35);
			
			putBarrierLine(10, 15, 25);
			putBarrierLine(10, 35, 45);
			
			putBarrierLine(16, 25, 35);
			putBarrierLine(17, 22, 26);
			putBarrierLine(17, 34, 38);
			
			putBarrierVert(20,11,15);
			putBarrierVert(40,11,15);
			break;
		default:
			level = 1;
			lvlMapInit();
			break;
	}
}

void lvlMapInit() {
	memset(lvlMap, SYMBOL_NOTHING, sizeof(lvlMap));
	
	lvlMapPuzzle();
	
	for(int i = 0; i < width; i++) {
		lvlMap[0][i] = SYMBOL_WALL;
		lvlMap[height-1][i] = SYMBOL_GRID;
	}
	
	for(int i = 0; i < height; i++)
		lvlMap[i][0] = lvlMap[i][width-1] = SYMBOL_WALL;
}

void lvlMapPut() {
	memset(map, 0, sizeof(map));
	for(int i = 0; i < height; i++)
		memcpy(map[i], lvlMap[i], sizeof(**lvlMap) * width);
}
