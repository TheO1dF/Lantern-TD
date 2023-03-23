
#include "fxlib.h"
#include "Fun.h"
#include "stdlib.h"
#include "pine-ini.h"
#include "ffun.h"
#include "string.h"
#include "astara.h"
#include "monster.h"

#define MAX_NUM_OF_TOWER 1024
#define MAX_NUM_OF_MONSTER 100

void pop_when_quit(void)
{
    unsigned int key;
    PopUpWin(3);
    locate(7, 3);
    Print((unsigned char *)"QUIT GAME");
    locate(5, 5);
    Print((unsigned char *)"Press [EXE] key");
    do
    {
        GetKey(&key);
    } while (key != KEY_CTRL_EXE);
}

int AddIn_main(int isAppli, unsigned short OptionNum)
{

    // Initialization

    PineIniFile *iniResult;
    PineIniError errorRet;
    PineIniSection *Section;

    char *TowerINIText;
    char *MonsterINIText;

    int filehandle;

    unsigned int key, i, j, round, IsPlace, IsPlaceOver, IsGameOver;
    long point;
    double Time, timeIndex;
    int Maps[37][37];
    int Direction[4096];
    LPTOWER Tower_DataBase[MAX_NUM_OF_TOWER];
    LPTOWERPLACE Tower_PlaceTower[MAX_NUM_OF_TOWER];
    LPTOWERPLACE Tower_Buffer[5];
    LPMONSTER Monster_DataBase[MAX_NUM_OF_MONSTER];
    LPMONSTERLIVE Monster_LiveMonster[MAX_NUM_OF_MONSTER];

    LPBASE base;

    int numOfPlace, numOfCurrent, numOfDirection, numOfMonster, numOfCreate;
    int Tower_DbSize = 0, Monster_DbSize = 0;

    POSITION Cursor_position, screen_position;
    LPPOSITION Cursor_Position, Current_Screen;

    Cursor_Position = &Cursor_position;
    Current_Screen = &screen_position;

    Current_Screen->x = 0;
    Current_Screen->y = 0;
    Cursor_Position->x = 0;
    Cursor_Position->y = 0;

    Time = 0.1;
    timeIndex = 0;
    round = 1;
    IsPlace = 1;
    IsPlaceOver = 0;
    IsGameOver = 0;
    numOfPlace = 0;
    numOfCurrent = 0;
    numOfDirection = 0;
    numOfCreate = 0;
    numOfMonster = 0;
    point = 0;

    base = (LPBASE)malloc(sizeof(base));
    base->damage = 0;
    base->health = 100;

    SetQuitHandler(pop_when_quit);

    // TowerDbRead
    filehandle = read_text_file(&TowerINIText, (char *)"\\\\crd0\\tower.txt");

    if (filehandle <= 0)
    {
        PopUpWin(3);
        locate(5, 3);
        Print((unsigned char *)"Read DATABASE");
        locate(5, 4);
        Print((unsigned char *)"ERROR");
        locate(5, 5);
        Print((unsigned char *)"Press [EXE] key");
        do
        {
            GetKey(&key);
        } while (key != KEY_CTRL_EXE);
        return 0;
    }

    iniResult = PineIni_Parse(TowerINIText, &errorRet);
    free(TowerINIText);

    if (iniResult == NULL)
    {
        PopUpWin(5);
        locate(9, 2);
        Print((unsigned char *)"ERROR");
        printf_pop_xy(5, 3, "Error Code:%d", errorRet.errorCode);
        printf_pop_xy(5, 4, "Line Number:%d", errorRet.lineNumber);
        locate(5, 5);
        Print((unsigned char *)"Press [EXE] key");
        do
        {
            GetKey(&key);
        } while (key != KEY_CTRL_EXE);
        return 0;
    }

    for (i = 0; i < iniResult->numSection; i++)
    {
        Section = iniResult->sections[i];
        if (strstr(Section->name, "tower"))
        {
            Tower_DataBase[Tower_DbSize] = (LPTOWER)malloc(sizeof(Tower));
            Tower_DataBase[Tower_DbSize]->id = PineIni_Section_GetInt(Section, "id", 0);
            Tower_DataBase[Tower_DbSize]->Tower_Level = PineIni_Section_GetInt(Section, "Tower_Level", 0);
            Tower_DataBase[Tower_DbSize]->Attack = PineIni_Section_GetFloat(Section, "Attack", 0);
            Tower_DataBase[Tower_DbSize]->Attack_Frequency = PineIni_Section_GetFloat(Section, "Attack_Frequency", 0);
            Tower_DataBase[Tower_DbSize]->Attack_Range = PineIni_Section_GetInt(Section, "Attack_Range", 0);
            Tower_DbSize++;
        }
    }

    // MonsterDbRead
    filehandle = read_text_file(&MonsterINIText, (char *)"\\\\crd0\\monster.txt");

    if (filehandle <= 0)
    {
        PopUpWin(3);
        locate(5, 3);
        Print((unsigned char *)"Read DATABASE");
        locate(5, 4);
        Print((unsigned char *)"ERROR");
        locate(5, 5);
        Print((unsigned char *)"Press [EXE] key");
        do
        {
            GetKey(&key);
        } while (key != KEY_CTRL_EXE);
        return 0;
    }

    iniResult = PineIni_Parse(MonsterINIText, &errorRet);
    free(MonsterINIText);

    if (iniResult == NULL)
    {
        PopUpWin(5);
        locate(9, 2);
        Print((unsigned char *)"ERROR");
        printf_pop_xy(5, 3, "Error Code:%d", errorRet.errorCode);
        printf_pop_xy(5, 4, "Line Number:%d", errorRet.lineNumber);
        locate(5, 5);
        Print((unsigned char *)"Press [EXE] key");
        do
        {
            GetKey(&key);
        } while (key != KEY_CTRL_EXE);
        return 0;
    }
    for (i = 0; i < iniResult->numSection; i++)
    {
        Section = iniResult->sections[i];
        if (strstr(Section->name, "monster"))
        {
            Monster_DataBase[Monster_DbSize] = (LPMONSTER)malloc(sizeof(Monster));
            Monster_DataBase[Monster_DbSize]->id = PineIni_Section_GetInt(Section, "id", 0);
            Monster_DataBase[Monster_DbSize]->Monster_Level = PineIni_Section_GetInt(Section, "Monster_Level", 0);
            Monster_DataBase[Monster_DbSize]->health = PineIni_Section_GetFloat(Section, "health", 0);
            Monster_DataBase[Monster_DbSize]->damage = PineIni_Section_GetFloat(Section, "damage", 0);
            Monster_DataBase[Monster_DbSize]->attack = PineIni_Section_GetFloat(Section, "attack", 0);
            Monster_DataBase[Monster_DbSize]->Speed = PineIni_Section_GetFloat(Section, "Speed", 0);
            Monster_DataBase[Monster_DbSize]->armor = PineIni_Section_GetFloat(Section, "armor", 0);
            Monster_DataBase[Monster_DbSize]->buff = PineIni_Section_GetInt(Section, "buff", 0);
            Monster_DataBase[Monster_DbSize]->debuff = PineIni_Section_GetInt(Section, "debuff", 0);
            Monster_DbSize++;
        }
    }

    for (i = 0; i < 37; i++)
    {
        for (j = 0; j < 37; j++)
        {
            if (i % 2 == 0)
            {
                if (j % 2 == 0)
                {
                    Maps[i][j] = 1;
                }
                else
                {
                    Maps[i][j] = 0;
                }
            }
            else
            {
                if (j % 2 == 1)
                {
                    Maps[i][j] = 1;
                }
                else
                {
                    Maps[i][j] = 0;
                }
            }
        }
    }

    for (i = 0; i < 37; i++)
    {
        for (j = 0; j < 37; j++)
        {
            if (j == 18)
            {
                if (i <= 8 || i >= 28)
                {
                    Maps[i][j] = 49;
                }
            }
            if (i == 18)
            {
                if (j <= 8 || j >= 28)
                {
                    Maps[i][j] = 49;
                }
            }
        }
    }
    Maps[2][4] = 2;
    Maps[32][34] = 3;
    Maps[18][4] = 4;
    Maps[18][32] = 5;
    Maps[4][32] = 6;
    Maps[4][18] = 7;
    Maps[32][18] = 8;

    // test astar
    // Astar(2, 4, 4, 18, 37, (int *)Maps, OpenList, CloseList, Direction, &numOFDirection);
    // for (i = 0; i < numOFDirection; i++)
    // {
    //     switch (Direction[i])
    //     {
    //     case 1:
    //         printf_pop_xy(1 + ((i % 10) * 2), 1 + i / 10, "U,");
    //         break;
    //     case 2:
    //         printf_pop_xy(1 + ((i % 10) * 2), 1 + i / 10, "D,");
    //         break;
    //     case 3:
    //         printf_pop_xy(1 + ((i % 10) * 2), 1 + i / 10, "L,");
    //         break;
    //     case 4:
    //         printf_pop_xy(1 + ((i % 10) * 2), 1 + i / 10, "R,");
    //         break;
    //     }
    // }

    // do
    // {
    //     GetKey(&key);
    // } while (key != KEY_CHAR_0);

    EnterGame();

    do
    {
        GetKey(&key);
    } while (key != KEY_CTRL_EXE);
    PopUpWin(3);
    locate(7, 3);
    Print((unsigned char *)"START GAME");
    locate(5, 5);
    Print((unsigned char *)"Press [0] key");
    do
    {
        GetKey(&key);
    } while (key != KEY_CHAR_0);
    while (1)
    {
        if (!IsGameOver)
        {
            key = 0;
            if (IsPlace)
            {
                Bdisp_AllClr_DDVRAM();
                printf_xy(42, 25, 0, "Round:%d", round);
                Sleep(1000);

                while (1)
                {
                    // Bdisp_AllClr_DDVRAM();
                    Bdisp_AllClr_VRAM();
                    Tower_Place(key, Cursor_Position, Current_Screen, Maps, Tower_DataBase, Tower_DbSize, Tower_PlaceTower, Tower_Buffer, &numOfPlace, &numOfCurrent, Direction, &numOfDirection, &IsPlaceOver);
                    Cursor_Move(key, Cursor_Position, Current_Screen);
                    Map_Initialization(Maps, Current_Screen, Cursor_Position, numOfCurrent);
                    Bdisp_PutDisp_DD();
                    if (numOfPlace > 0 && IsPlaceOver)
                    {
                        IsPlace = 0;
                        break;
                    }

                    GetKey(&key);

                    Open_Map(key, Maps);
                    Jump_View(key, Current_Screen);
                    Check_Status(key, Cursor_Position, Current_Screen, Maps, Tower_PlaceTower, Tower_DataBase, numOfPlace, Tower_DbSize);
                }
            }
            else
            {
                while (1)
                {
                    Bdisp_AllClr_VRAM();
                    if (numOfCreate < 10)
                    {
                        if ((int)(timeIndex * 10) % 15 == 0)
                        {
                            Monster_Create(Monster_DataBase, Monster_LiveMonster, Monster_DbSize, &numOfMonster, round);
                            numOfCreate++;
                        }
                    }
                    if (numOfMonster != 0)
                    {
                        for (i = 0; i < numOfMonster; i++)
                        {
                            if (!Monster_Move(Direction, numOfDirection, Maps, Monster_LiveMonster[i], &numOfMonster, base, Time))
                            {
                                base->damage = base->damage + Monster_LiveMonster[i]->Monster_Live->attack;
                                free_Monster(Monster_LiveMonster, &numOfMonster, i);
                            }
                        }
                    }

                    Screen_Move(Current_Screen);
                    Battle_Map(Maps, Current_Screen, Current_Screen, Monster_LiveMonster, numOfMonster);
                    Bdisp_PutDisp_DD();
                    Tower_Attack(Tower_PlaceTower, numOfPlace, Monster_LiveMonster, numOfMonster);
                    Check_MonsterLive(Monster_LiveMonster, &numOfMonster);
                    if (base->damage >= base->health)
                    {
                        IsGameOver = 1;
                        break;
                    }
                    if (!numOfMonster)
                    {
                        if (numOfCreate >= 10)
                        {
                            numOfCreate = 0;
                            IsPlaceOver = 0;
                            IsPlace = 1;
                            round++;
                            timeIndex = 0;
                            break;
                        }
                    }
                    Sleep((int)(Time*1000));
                    timeIndex += Time;
                }
            }
        }

        else
        {
            break;
        }
    }

    free(Tower_DataBase);
    free(Tower_Buffer);
    free(Tower_PlaceTower);
    return 1;
}

#pragma section _BR_Size
unsigned long BR_Size;
#pragma section

#pragma section _TOP

int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section
