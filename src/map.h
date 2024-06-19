
#define width 65
#define height 25

#define ConsoleWidth 100
#define ConsoleHeight 35

extern char map[height][width+1];

int IsMapCellExists(int mapY, int mapX);
int IsConsoleCellExists(int mapY, int mapX);
void mapInit();
