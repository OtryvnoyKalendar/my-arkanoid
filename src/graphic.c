#include <string.h> // для memset()

#include "map.h"
#include "main.h"
#include "core.h"
#include "math.h"

// отрисовка игры

void ClearMap() {
	memset(map, SYMBOL_NOTHING, sizeof(map));
}

void PutSymbolToConsole(int y, int x, char ch, int color) {
	if(!IsConsoleCellExists(y, x))
		ErrorCloseProgram("выход за границы игрового поля");
	
	map[y][x] = ch;
	move(y, x);
	if(color != -1)
		attron(COLOR_PAIR(color));
	addch(ch);
}

void DrawSymbolInConsole(int y, int x, char ch, int color) {
	if(!IsConsoleCellExists(y, x))
		ErrorCloseProgram("выход за границы игрового поля");
	
	move(y, x);
	if(color != -1)
		attron(COLOR_PAIR(color));
	addch(ch);
}

void PutText(const char* message, int ystart, int xstart, int color) {
	for(int i=0; message[i]!='\0'; i++)
		if (IsConsoleCellExists(ystart, xstart+i))
			DrawSymbolInConsole(ystart, xstart+i, message[i], color);
	refresh();
}
