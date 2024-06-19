
#define width 65
#define height 25

#define ConsoleWidth 120
#define ConsoleHeight 40

extern char map[height][width+1];

int IsMapCellExists(int mapY, int mapX);
int IsConsoleCellExists(int mapY, int mapX);
void mapInit();
