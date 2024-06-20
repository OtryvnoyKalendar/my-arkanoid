#include <math.h> // для sin(), cos()
#include <stdlib.h> // для rand()

// gcc-специфично
#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })

#define max(x, y) ({				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(void) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; })

#include "map.h"
#include "main.h"
#include "gameplay.h"
#include "core.h"
#include "object.h"

#define RacketSizeMax 15
#define RacketSizeMin 5

tObj objArr[ObjArrSize];
int ObjArrCnt = 0;

char objUpgradeTypes[] = {SYMBOL_WIDE, SYMBOL_THIN, SYMBOL_FIRE};
int objUpgradeTypesCnt = sizeof(objUpgradeTypes) / sizeof(objUpgradeTypes[0]);

void CorrectAngle(float* a) {
	if(*a < 0)
		*a += M_PI*2;
	if(*a > M_PI*2)
		*a -= M_PI*2;
}

tObj ObjCreate(float x, float y, float alfa, float speed, char type) {
	return (tObj){x, y, (int)x, (int)y, alfa, speed, type};
}

void ObjPut(tObj obj) {
	if(IsMapCellExists(obj.iy, obj.ix))
		if(map[obj.iy][obj.ix] == SYMBOL_NOTHING)
				map[obj.iy][obj.ix] = obj.type;
}

void ObjChanceCreateRandUpgradeObject(float y, float x) {
	int i = rand() % objUpgradeTypesRandMax;
	if(i < objUpgradeTypesCnt)
		ObjArr_Add(ObjCreate(x, y, M_PI_2, objUpgradeSpeed, objUpgradeTypes[i]));
}

void ObjWorkUpgrade(tObj* obj) {
	if(map[obj->iy][obj->ix] != SYMBOL_ROCKET)
		return;
	
	if(obj->type == SYMBOL_WIDE)
		rocket.size = min(rocket.size+1, RacketSizeMax);
	else if (obj->type == SYMBOL_THIN)
		rocket.size = max(rocket.size-1, RacketSizeMin);
	else if (obj->type == SYMBOL_FIRE)
		rocket.fireMode = 1;
	else
		ErrorCloseProgram("неизвестный тип улучшения");
	
	obj->del = 1;
}

void ObjMove(tObj* obj) {
	CorrectAngle(&(obj->alfa));
	
	obj->x += cos(obj->alfa) * obj->speed;
	obj->y += sin(obj->alfa) * obj->speed;
	
	obj->ix = (int)obj->x;
	obj->iy = (int)obj->y;
}

int ObjHitBrick(tObj ball) {
	if (map[ball.iy][ball.ix] == SYMBOL_BRICK) {
		if(lvlMap[ball.iy][ball.ix] == SYMBOL_BRICK) // шизопроверка?
			ObjChanceCreateRandUpgradeObject(ball.y, ball.x);
		
		int brickNum = (ball.ix-1) / BrickWidth;
		int dx = 1 + brickNum * BrickWidth;
		for(int i = 0; i < BrickWidth; i++) {
			static char* c;
			c = &lvlMap[ball.iy][i + dx];
			if(*c == SYMBOL_BRICK)
				*c = SYMBOL_NOTHING;
		}
		return 1;
	}
	return 0;
}

void ObjWorkBullet(tObj* obj) {
	if(obj->type != SYMBOL_BULLET)
		return;
	
	if(ObjHitBrick(*obj) || map[obj->iy][obj->ix] == SYMBOL_WALL)
		obj->del = 1;
}

void ObjWork(tObj* obj) {
	ObjMove(obj);
	ObjWorkUpgrade(obj);
	ObjWorkBullet(obj);
}

void ObjArr_Add(tObj obj) {
	if( !(ObjArrCnt+1 < ObjArrSize) )
		ErrorCloseProgram("массив объектов полностью заполнен");
	objArr[ObjArrCnt] = obj;
	ObjArrCnt++;
}

void ObjArr_DelPos(int pos) {
	if(pos < 0 || pos > ObjArrCnt)
		ErrorCloseProgram("такой позиции в массиве нет");
	objArr[pos] = objArr[ObjArrCnt-1];
	ObjArrCnt--;
}

void ObjArr_Work() {
	int i = 0;
	while(i < ObjArrCnt) {
		ObjWork(objArr+i);
		if(objArr[i].y < 0 || objArr[i].y > height || objArr[i].del)
			ObjArr_DelPos(i);
		else
			i++;
	}
}

void ObjArr_Put() {
	for(int i = 0; i < ObjArrCnt; i++)
		ObjPut(objArr[i]);
}

void ObjArr_Clear() {
	ObjArrCnt = 0;
}
