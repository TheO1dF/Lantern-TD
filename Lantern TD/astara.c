#include "fxlib.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "astara.h"

// find min f from OpenList
LPNODE GetNodeFormOpen(LPSTACK Open)
{
    LPSTACK temp, min, minP;
    LPNODE minx;

    temp = Open->next;
    min = Open->next;
    minP = Open;

    if (temp == NULL)
    {
        return NULL;
    }
    while (temp->next != NULL)
    {
        if ((temp->next->nPoint->f) < (min->nPoint->f))
        {
            min = temp->next;
            minP = temp;
        }
        temp = temp->next;
    }
    minx = min->nPoint;
    temp = minP->next;
    minP->next = minP->next->next;
    free(temp);
    return minx;
}

LPNODE CheckList(LPSTACK List, int row, int col)
{
    LPSTACK temp = List->next;
    if (temp == NULL)
        return NULL;
    while (temp != NULL)
    {
        if ((temp->nPoint->row == row) && (temp->nPoint->col == col))
        {
            return temp->nPoint;
        }
        else
        {
            temp = temp->next;
        }
    }
    return NULL;
}

// Put Node in List
void PutNodeInList(LPNODE Node, LPSTACK List)
{
    LPSTACK temp;
    temp = (LPSTACK)malloc(sizeof(Stack));
    temp->nPoint = Node;

    temp->next = List->next;
    List->next = temp;
}

int GetH(int row, int col, int d_row, int d_col)
{
    return (abs(d_row - row) + abs(d_col - col));
}

int IsCanMove(int row, int col, int Max, int *Map)
{
    if (row < 0 || row >= Max)
        return 0;
    if (col < 0 || col >= Max)
        return 0;
    return Map[row * 37 + col] < 49;
}

void CreateNode(LPNODE bestNode, int row, int col, LPSTACK OpenList, LPSTACK CloseList, int d_row, int d_col, int *DirectionIndex)
{
    int g;
    LPNODE oldNode, temp;

    g = bestNode->g + 1;
    if (CheckList(CloseList, row, col) != NULL)
    {
        oldNode = NULL;
        if (CheckList(OpenList, row, col) != NULL)
        {
            oldNode = CheckList(OpenList, row, col);
            oldNode->parent = bestNode;
            oldNode->g = g;
            oldNode->f = g + oldNode->h;
        }
    }
    else
    {
        temp = (LPNODE)malloc(sizeof(Node));
        temp->parent = bestNode;
        temp->g = g;
        temp->h = GetH(row, col, d_row, d_col);
        temp->f = temp->g + temp->h;
        temp->row = row;
        temp->col = col;
        *DirectionIndex = *DirectionIndex + 1;
        temp->direction = *DirectionIndex;

        PutNodeInList(temp, OpenList);
    }
}

void SeachSecessionNode(LPNODE bestNode, int Max, int *Map, LPSTACK OpenList, LPSTACK CloseList, int d_row, int d_col, int *DirectionIndex)
{
    int row, col;
    if (IsCanMove(bestNode->row - 1, bestNode->col, Max, Map))
    {
        row = bestNode->row - 1;
        col = bestNode->col;
        CreateNode(bestNode, row, col, OpenList, CloseList, d_row, d_col, DirectionIndex);
    }
    if (IsCanMove(bestNode->row + 1, bestNode->col, Max, Map))
    {
        row = bestNode->row + 1;
        col = bestNode->col;
        CreateNode(bestNode, row, col, OpenList, CloseList, d_row, d_col, DirectionIndex);
    }
    if (IsCanMove(bestNode->row, bestNode->col - 1, Max, Map))
    {
        row = bestNode->row;
        col = bestNode->col - 1;
        CreateNode(bestNode, row, col, OpenList, CloseList, d_row, d_col, DirectionIndex);
    }
    if (IsCanMove(bestNode->row, bestNode->col + 1, Max, Map))
    {
        row = bestNode->row;
        col = bestNode->col + 1;
        CreateNode(bestNode, row, col, OpenList, CloseList, d_row, d_col, DirectionIndex);
    }
    PutNodeInList(bestNode, CloseList);
}

int ListClear(LPSTACK List)
{
    LPSTACK temp, head;
    LPNODE p_node;

    temp = List->next;
    if (temp == NULL)
    {
        return 1;
    }
    while (temp != NULL)
    {
        head = temp;
        temp = temp->next;
        p_node = head->nPoint;
        free(p_node);
        free(head);
        List->next = temp;
    }
    return 1;
}

int Astar(int startX, int startY, int destinationX, int destinationY, int Max, int *Map, LPSTACK OpenList, LPSTACK CloseList, int *Direction, int *numOFDirection)
{
    LPNODE startNode = (LPNODE)malloc(sizeof(Node));
    LPNODE bestNode, temp, temp_parent;
    int index, nodeSum, nodeIndex, directionIndex;

    index = 0;
    nodeSum = 0;
    nodeIndex = 0;
    directionIndex = 0;
    bestNode = NULL;

    startNode->parent = NULL;
    startNode->row = startX;
    startNode->col = startY;
    startNode->g = 0;
    startNode->h = GetH(startNode->row, startNode->col, destinationX, destinationY);
    startNode->f = startNode->g + startNode->h;
    startNode->direction = 0;
    PutNodeInList(startNode, OpenList);

    while (1)
    {
        bestNode = GetNodeFormOpen(OpenList);
        if (bestNode == NULL)
        {
            return 0;
        }
        else if (bestNode->row == destinationX && bestNode->col == destinationY)
        {
            temp = bestNode;
            while (temp->parent != NULL)
            {
                nodeSum++;
                temp = temp->parent;
            }
            temp = bestNode;
            nodeIndex = nodeSum - 1;
            *numOFDirection = nodeSum;
            while (temp->parent != NULL && nodeIndex >= 0)
            {
                temp_parent = temp->parent;
                if (temp_parent->col - temp->col == 0 && temp_parent->row - temp->row == 1)
                {
                    Direction[nodeIndex] = 1; // Up
                }
                else if (temp_parent->col - temp->col == 0 && temp_parent->row - temp->row == -1)
                {
                    Direction[nodeIndex] = 2; // Down
                }
                else if (temp_parent->col - temp->col == 1 && temp_parent->row - temp->row == 0)
                {
                    Direction[nodeIndex] = 3; // Left
                }
                else if (temp_parent->col - temp->col == -1 && temp_parent->row - temp->row == 0)
                {
                    Direction[nodeIndex] = 4; // Right
                }
                else
                {
                    Direction[nodeIndex] = 0;
                }
                nodeIndex--;
                temp = temp->parent;
            }
            return 1;
        }
        index++;
        SeachSecessionNode(bestNode, Max, Map, OpenList, CloseList, destinationX, destinationY, &directionIndex);
    }
}
