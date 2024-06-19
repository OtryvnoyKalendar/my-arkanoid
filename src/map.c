#include "map.h"
#include "main.h"

char map[height][width+1];

int IsMapCellExists(int mapY, int mapX) {
	return (mapY >= 0 && mapY < height && mapX >= 0 && mapX < width);
}

int IsConsoleCellExists(int mapY, int mapX) {
	return (mapY >= 0 && mapY < ConsoleHeight && mapX >= 0 && mapX < ConsoleWidth);
}

void putBarrierLine(int line, int xStart, int xEnd) {
	if (xStart<xEnd)
		for(int i=xStart; i<xEnd;i++)
			map[line][i] = SYMBOL_WALL;
}
void putBarrierVert(int line, int xStart, int xEnd) {
	if (xStart<xEnd)
		for(int i=xStart; i<xEnd;i++)
			map[i][line] = SYMBOL_WALL;
}

void mapInit() {
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++) {
			map[i][j] = SYMBOL_WALL;
			if (i>=1 && i<= height-2 && j>=1 && j<= width-2)
				map[i][j] = SYMBOL_NOTHING;
			else if (i == height-1 && j<= width-1)
				map[i][j] = SYMBOL_GRID;
		}
	
	if (level == 1) {
		putBarrierLine(7, 25, 40);
		putBarrierVert(25,4,8);
		putBarrierVert(40,4,8);
	}
	else if (level == 2) {
		putBarrierLine(10, 20, 45);
		putBarrierVert(18,7,15);
		putBarrierVert(46,7,15);
	}
	else if (level == 3) {
		putBarrierLine(10, 5, 10);
		putBarrierLine(10, 15, 20);		
		putBarrierLine(10, 25, 30);
		putBarrierLine(10, 35, 40);
		
		putBarrierLine(15, 30, 40);
		putBarrierLine(15, 42, 60);
	}
	else if (level == 4) {
		putBarrierLine(5, 25, 35);
		
		putBarrierLine(10, 15, 25);
		putBarrierLine(10, 35, 45);
		
		putBarrierLine(16, 25, 35);
		putBarrierLine(17, 22, 26);
		putBarrierLine(17, 34, 38);

		putBarrierVert(20,11,15);
		putBarrierVert(40,11,15);
	}
	else
		level = 1;
}
