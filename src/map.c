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
			for(int i = 7; i < width-7; i++)
				lvlMap[5][i] = lvlMap[6][i] = SYMBOL_BRICK;
			break;
		case 2:
			for(int i = 19; i <= 48; i++) {
				lvlMap[1][i] = lvlMap[2][i] = SYMBOL_BRICK;
				lvlMap[8][i] = lvlMap[9][i] = SYMBOL_BRICK;
				lvlMap[10][i] = SYMBOL_WALL;
			}
			break;
		case 3:
			for(int j = 1; j < 10; j++)
				for(int i = 1; i < 62; i += 6)
					lvlMap[j][i] = lvlMap[j][i+1] = lvlMap[j][i+2] = SYMBOL_BRICK;
			break;
		default:
			level = 1;
			lvlMapInit();
			break;
	}
}

int lvlMapBrickCount() {
	int cnt = 0;
	
	for(int j = 0; j < height; j++)
		for(int i = 0; i < width; i++)
			if(lvlMap[j][i] == SYMBOL_BRICK)
				cnt++;
	
	return cnt;
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
