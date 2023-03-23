#ifndef __FUN_H__
#define __FUN_H__

#include "astara.h"

typedef struct tag_Position
{
    int x;
    int y;
} POSITION, *LPPOSITION;

typedef struct tag_Tower
{
    int id;
    int Tower_Level;
    double Attack;
    double Attack_Frequency;
    int Attack_Range; // diameter
} Tower, *LPTOWER;

typedef struct tag_Tower_Place
{
    LPTOWER Place_Tower;
    LPPOSITION position;
} TOWERPLACE, *LPTOWERPLACE;

typedef struct tag_Base
{
    double health;
    double damage;
} Base, *LPBASE;
typedef struct tag_Monster
{
    int id;
    int Monster_Level;
    double health;
    double damage;
    double attack;
    double Speed;
    double armor;
    int(*ability);
    int buff;
    int debuff;
} Monster, *LPMONSTER;

typedef struct tag_Monster_Live
{
    LPMONSTER Monster_Live;
    LPPOSITION position;
    LPPOSITION target_position;
    int MoveStep;
    int Move_Distance;
    int IsMoveComplete;
} Monster_Live, *LPMONSTERLIVE;

// Prototypes
void printf_xy(int x, int y, int mode, const char *format, ...);
void printf_pop_xy(int x, int y, const char *format, ...);
int my_atoi(const char *str);
void draw_picture(int x, int y, int width, int height, int kind, int mod, unsigned char *pGraph);
void area_clear(int left, int top, int right, int bottom, int sel);
void Cursor_Move(unsigned int key, LPPOSITION last_position, LPPOSITION Current_Screen);
void Screen_Move(LPPOSITION Screen_position);
void Map_Initialization(int *Map_Array, LPPOSITION Current_Screen, LPPOSITION last_position, int numOfCurrent);
void Battle_Map(int *Map_Array, LPPOSITION Current_Screen, LPPOSITION last_position, LPMONSTERLIVE Monster_LiveMonster[], int numOfMonster);
void Tower_Place(unsigned int key, LPPOSITION Cursor_Position, LPPOSITION Screen_Position, int *Map, LPTOWER Tower_DataBase[], int Tower_DbSize, LPTOWERPLACE Tower_PlaceTower[], LPTOWERPLACE Tower_Buffer[5], int *numOfPlace, int *numOfCurrent, int *Direction, int *numOfDirection,int* IsPlaceOver);
void Open_Map(unsigned int key, int *Map);
void Jump_View(unsigned int key, LPPOSITION Screen_Position);
void Check_Status(unsigned int key, LPPOSITION Cursor_Position, LPPOSITION Screen_Position, int *Map, LPTOWERPLACE Tower_PlaceTower[], LPTOWER Tower_Database[], int numOfTower, int Tower_DbSize);
void EnterGame(void);
int Check_Path(int *Map, int *Direction, int *numOfDirection);
void Tower_Attack(LPTOWERPLACE Tower_PlaceTower[], int numOfTower, LPMONSTERLIVE Monster_LiveMonster[], int numOfMonster);
char GetNumber(unsigned int key);
int free_Tower(LPTOWERPLACE Tower_PlaceTower[], int *numOfTower, int needFree_index);
int free_Monster(LPMONSTERLIVE Monster_LiveMonster[], int *numOfMonster, int needFree_index);

#endif