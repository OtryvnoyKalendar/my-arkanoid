#pragma once

#define ObjArrSize 1000
extern tObj objArr[ObjArrSize];
extern int ObjArrCnt;

#define objUpgradeTypesRandMax 7

tObj ObjCreate(float x, float y, float alfa, float speed, char type);
void ObjWork(tObj* obj);
void ObjPut(tObj obj);
void ObjArr_Add(tObj obj);
void ObjArr_Work();
void ObjArr_Put();
