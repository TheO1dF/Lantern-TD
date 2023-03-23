#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Fun.h"

void Data_Match_M(LPMONSTERLIVE monster, LPMONSTER monster_db, int x, int y,int round);
void Monster_Create(LPMONSTER Monster_DataBase[], LPMONSTERLIVE Monster_liveMonster[], int numOfDbSize_M, int *numOfMonster, int round);
int Monster_Move(int *Direction, int numOfDirection, int *Map, LPMONSTERLIVE Monster_LiveMonster, int *numOfMonster, LPBASE base, double Time);
void Check_MonsterLive(LPMONSTERLIVE Monster_LiveMonster[], int *numOfMonster);

#endif