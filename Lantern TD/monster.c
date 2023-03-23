#include "fxlib.h"
#include "Fun.h"
#include "monster.h"
#include "astara.h"
#include "stdlib.h"
#include "math.h"

LPPOSITION Check_Direction(int index, LPPOSITION position)
{
    switch (index)
    {
    case 1:
        position->x = position->x - 1;
        return position;
    case 2:
        position->x = position->x + 1;
        return position;
    case 3:
        position->y = position->y - 1;
        return position;
    case 4:
        position->y = position->y + 1;
        return position;
    default:
        return NULL;
    }
}

void Data_Match_M(LPMONSTERLIVE monster, LPMONSTER monster_db, int x, int y, int round)
{
    monster->Monster_Live->id = monster_db->id;
    monster->Monster_Live->Monster_Level = monster_db->Monster_Level;
    monster->Monster_Live->health = monster_db->health + 10 * round;
    monster->Monster_Live->damage = monster_db->damage;
    monster->Monster_Live->attack = monster_db->attack;
    monster->Monster_Live->Speed = monster_db->Speed;
    monster->Monster_Live->armor = monster_db->armor;
    monster->Monster_Live->buff = monster_db->buff;
    monster->Monster_Live->debuff = monster_db->debuff;
    monster->position->x = x;
    monster->position->y = y;
    monster->target_position->x = x;
    monster->target_position->y = y;
    monster->MoveStep = 0;
    monster->Move_Distance = 0;
    monster->IsMoveComplete = 1;
}

void Monster_Create(LPMONSTER Monster_DataBase[], LPMONSTERLIVE Monster_liveMonster[], int numOfDbSize_M, int *numOfMonster, int round)
{
    int i;

    for (i = 0; i < numOfDbSize_M; i++)
    {
        if (Monster_DataBase[i]->id == (round % 5) + 100)
        {

            Monster_liveMonster[*numOfMonster] = (LPMONSTERLIVE)malloc(sizeof(Monster_Live));
            Monster_liveMonster[*numOfMonster]->Monster_Live = (LPMONSTER)malloc(sizeof(Monster));
            Monster_liveMonster[*numOfMonster]->position = (LPPOSITION)malloc(sizeof(POSITION));
            Monster_liveMonster[*numOfMonster]->target_position = (LPPOSITION)malloc(sizeof(POSITION));
            Data_Match_M(Monster_liveMonster[*numOfMonster], Monster_DataBase[i], 2, 4, round);
            Monster_liveMonster[*numOfMonster]->Monster_Live->ability = NULL;
            *numOfMonster = *numOfMonster + 1;

            break;
        }
    }
}

int Monster_Move(int *Direction, int numOfDirection, int *Map, LPMONSTERLIVE Monster_LiveMonster, int *numOfMonster, LPBASE base, double Time)
{

    LPPOSITION Move;
    int direction_x = 0, direction_y = 0;

    if (Monster_LiveMonster->IsMoveComplete)
    {
        if (Monster_LiveMonster->MoveStep >= numOfDirection)
        {
            return 0;
        }
        else
        {
            Move = Check_Direction(Direction[Monster_LiveMonster->MoveStep], Monster_LiveMonster->target_position);
            Monster_LiveMonster->IsMoveComplete = 0;
        }
    }
    if (Move != NULL)
    {
        direction_x = Monster_LiveMonster->target_position->x - Monster_LiveMonster->position->x;
        direction_y = Monster_LiveMonster->target_position->y - Monster_LiveMonster->position->y;
        if (Monster_LiveMonster->Move_Distance < 15)
        {
            Monster_LiveMonster->Move_Distance += abs((int)((direction_x * (Monster_LiveMonster->Monster_Live->Speed)) * Time + (direction_y * (Monster_LiveMonster->Monster_Live->Speed)) * Time));
        }
        else
        {
            Monster_LiveMonster->IsMoveComplete = 1;
            Monster_LiveMonster->MoveStep += 1;
            Monster_LiveMonster->Move_Distance = 0;
            Monster_LiveMonster->position->x = Monster_LiveMonster->target_position->x;
            Monster_LiveMonster->position->y = Monster_LiveMonster->target_position->y;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void Check_MonsterLive(LPMONSTERLIVE Monster_LiveMonster[], int *numOfMonster)
{
    int i;
    for (i = 0; i < *numOfMonster; i++)
    {
        if ((Monster_LiveMonster[i]->Monster_Live->damage) >= (Monster_LiveMonster[i]->Monster_Live->health))
        {
            free_Monster(Monster_LiveMonster, numOfMonster, i);
        }
    }
}