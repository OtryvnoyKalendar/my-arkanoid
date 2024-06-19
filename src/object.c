#include <math.h>

#include "map.h"
#include "main.h"
#include "gameplay.h"
#include "core.h"
#include "object.h"

tObj objArr[ObjArrSize];
int ObjArrCnt = 0;

char objUpgradeTypes[] = {SYMBOL_WIDE, SYMBOL_THIN};
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

void ObjMove(tObj* obj) {
	CorrectAngle(&(obj->alfa));
	
	obj->x += cos(obj->alfa) * obj->speed;
	obj->y += sin(obj->alfa) * obj->speed;
	
	obj->ix = (int)obj->x;
	obj->iy = (int)obj->y;
}

void ObjWork(tObj* obj) {
	ObjMove(obj);
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