#ifndef __ASTARA_H__
#define __ASTARA_H__

typedef struct tag_Node
{
    int f, g, h;
    int row;
    int col;
    int direction;
    struct tag_Node *parent;
} Node, *LPNODE;

typedef struct tag_Stack
{
    LPNODE nPoint;
    struct tag_Stack *next;
} Stack, *LPSTACK;

int ListClear(LPSTACK List);
int Astar(int startX, int startY, int destinationX, int destinationY, int Max, int *Map, LPSTACK OpenList, LPSTACK CloseList, int *Direction, int *numOFDirection);

#endif