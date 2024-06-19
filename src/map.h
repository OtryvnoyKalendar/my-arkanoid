
#define width	65
#define height	25

#define ConsoleWidth	100
#define ConsoleHeight	35

#define BrickWidth 3

extern char map[height][width+1];
extern char lvlMap[height][width];

int IsMapCellExists(int mapY, int mapX);
int IsConsoleCellExists(int mapY, int mapX);
//void mapInit();
void lvlMapInit();
void lvlMapPut();
