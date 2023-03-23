#include "fxlib.h"
#include "stdlib.h"
#include "stdio.h"
#include "Fun.h"
#include "stdarg.h"
#include "string.h"
#include "astara.h"
#include "monster.h"

const int SysCallWrapper[] = {0xD201422B, 0x60F20000, 0x80010070};
const int (*iSysCallFuncPtr)(int R4, int R5, int R6, int R7, int FNo) = (void *)&SysCallWrapper;

#define RTC_GetTicks() (int)(*iSysCallFuncPtr)(0, 0, 0, 0, 0x03B)
#define GETCODE(c1, c2) (gcode1 = (c1), gcode2 = (c2))

const unsigned char POINT[] = {
    0x80,
};
const unsigned char cursor_graph_[] =
    {
        0xF0,
        0xC0,
        0x80,
        0x81,
        0x81,
        0x1,
        0x3,
        0xF,
};
const char spawn_door_graph_[] =
    {
        0xFF,
        0xFF,
        0xBF,
        0xFD,
        0xC0,
        0x3,
        0xE0,
        0x7,
        0xEE,
        0x77,
        0xDE,
        0x7B,
        0x80,
        0x1,
        0xEF,
        0xF7,
        0xEF,
        0xF7,
        0xEF,
        0xF7,
        0xCF,
        0xF3,
        0xCF,
        0xF3,
        0xCF,
        0xF3,
        0xCF,
        0xF3,
        0x9F,
        0xF9,
        0xFF,
        0xFF,
};
const char base_graph_[] =
    {
        0x0,
        0x0,
        0x3F,
        0xFC,
        0x7C,
        0x1E,
        0x79,
        0xCE,
        0x73,
        0xC6,
        0x76,
        0xE6,
        0x76,
        0xE6,
        0x76,
        0xE6,
        0x75,
        0x66,
        0x75,
        0x66,
        0x76,
        0xE6,
        0x76,
        0xE6,
        0x76,
        0xE6,
        0x77,
        0xE6,
        0x3F,
        0xFC,
        0x0,
        0x0,
};
const char check_point_1_graph_[] =
    {
        0x0,
        0x0,
        0x7F,
        0xFE,
        0x5F,
        0xFA,
        0x7E,
        0x7E,
        0x7C,
        0x7E,
        0x78,
        0x7E,
        0x7E,
        0x7E,
        0x7E,
        0x7E,
        0x7E,
        0x7E,
        0x7E,
        0x7E,
        0x7E,
        0x7E,
        0x7E,
        0x7E,
        0x7F,
        0xFE,
        0x5F,
        0xFA,
        0x7F,
        0xFE,
        0x0,
        0x0,
};
const char check_point_2_graph_[] =
    {
        0x0,
        0x0,
        0x7F,
        0xFE,
        0x5F,
        0xFA,
        0x78,
        0x1E,
        0x78,
        0x1E,
        0x7F,
        0x9E,
        0x7F,
        0x9E,
        0x78,
        0x1E,
        0x78,
        0x1E,
        0x79,
        0xFE,
        0x79,
        0xFE,
        0x78,
        0x1E,
        0x78,
        0x1E,
        0x5F,
        0xFA,
        0x7F,
        0xFE,
        0x0,
        0x0,
};
const char check_point_3_graph_[] =
    {
        0x0,
        0x0,
        0x7F,
        0xFE,
        0x5F,
        0xFA,
        0x78,
        0x1E,
        0x78,
        0x1E,
        0x7F,
        0x9E,
        0x7F,
        0x9E,
        0x78,
        0x1E,
        0x78,
        0x1E,
        0x7F,
        0x9E,
        0x7F,
        0x9E,
        0x78,
        0x1E,
        0x78,
        0x1E,
        0x5F,
        0xFA,
        0x7F,
        0xFE,
        0x0,
        0x0,
};
const char check_point_4_graph_[] =
    {
        0x0,
        0x0,
        0x7F,
        0xFE,
        0x5F,
        0xFA,
        0x79,
        0x9E,
        0x79,
        0x9E,
        0x79,
        0x9E,
        0x79,
        0x9E,
        0x78,
        0x1E,
        0x78,
        0x1E,
        0x7F,
        0x9E,
        0x7F,
        0x9E,
        0x7F,
        0x9E,
        0x7F,
        0x9E,
        0x5F,
        0xFA,
        0x7F,
        0xFE,
        0x0,
        0x0,
};
const char check_point_5_graph_[] =
    {
        0x0,
        0x0,
        0x7F,
        0xFE,
        0x5F,
        0xFA,
        0x78,
        0x1E,
        0x78,
        0x1E,
        0x79,
        0xFE,
        0x79,
        0xFE,
        0x78,
        0x1E,
        0x78,
        0x1E,
        0x7F,
        0x9E,
        0x7F,
        0x9E,
        0x78,
        0x1E,
        0x78,
        0x1E,
        0x5F,
        0xFA,
        0x7F,
        0xFE,
        0x0,
        0x0,
};
const char Wall_graph_[] =
    {
        0x0,
        0x0,
        0x77,
        0xF6,
        0x77,
        0xF6,
        0x0,
        0x0,
        0x7E,
        0xFE,
        0x7E,
        0xFE,
        0x0,
        0x0,
        0x77,
        0xF6,
        0x77,
        0xF6,
        0x0,
        0x0,
        0x7D,
        0xFE,
        0x7D,
        0xFE,
        0x0,
        0x0,
        0x77,
        0xF6,
        0x77,
        0xF6,
        0x0,
        0x0,
};
const char Tile_Default_graph_[] =
    {
        0x0,
        0x0,
        0x12,
        0x48,
        0x24,
        0x92,
        0x49,
        0x24,
        0x12,
        0x48,
        0x24,
        0x92,
        0x49,
        0x24,
        0x12,
        0x48,
        0x24,
        0x92,
        0x49,
        0x24,
        0x12,
        0x48,
        0x24,
        0x92,
        0x49,
        0x24,
        0x12,
        0x48,
        0x24,
        0x92,
        0x0,
        0x0,
};
const char Tower_Default_graph_[] =
    {
        0x0,
        0x0,
        0x41,
        0xC0,
        0xA1,
        0x40,
        0xA7,
        0xF0,
        0x4F,
        0xF8,
        0xF,
        0xF8,
        0xF,
        0xF8,
        0x6,
        0x10,
        0x7,
        0xB0,
        0x6,
        0x10,
        0x6,
        0xD0,
        0x6,
        0x10,
        0x7,
        0xF0,
        0xF,
        0xF8,
        0x1F,
        0xFC,
        0x3F,
        0xFE,
};
const char Tower_1_graph_[] =
    {
        0x0,
        0x0,
        0x40,
        0x0,
        0xA1,
        0xE0,
        0xA1,
        0x20,
        0x47,
        0x38,
        0x3,
        0xF0,
        0x2,
        0x10,
        0x2,
        0xB0,
        0x2,
        0x10,
        0x2,
        0x50,
        0x7,
        0xF8,
        0x7,
        0xF8,
        0x1,
        0xE0,
        0x0,
        0xC0,
        0x0,
        0xC0,
        0x0,
        0x0,
};
const char Tower_2_graph_[] =
    {
        0x3,
        0xE0,
        0x44,
        0x10,
        0xA4,
        0x10,
        0xA4,
        0x10,
        0x44,
        0x10,
        0x7,
        0xF0,
        0x4,
        0x10,
        0xC,
        0x10,
        0xD,
        0x58,
        0xD,
        0x48,
        0x4,
        0x8,
        0x4,
        0x48,
        0x7,
        0xF8,
        0xF,
        0xFC,
        0x1F,
        0xFE,
        0x0,
        0x0,
};
const char Tower_3_graph_[] =
    {
        0x0,
        0x0,
        0x41,
        0xC0,
        0xA1,
        0x40,
        0xA3,
        0xE0,
        0x47,
        0xF0,
        0x8,
        0x8,
        0x10,
        0x4,
        0x22,
        0x12,
        0x22,
        0x12,
        0x22,
        0x12,
        0x20,
        0x2,
        0x10,
        0xC4,
        0x8,
        0x8,
        0x7,
        0xF0,
        0x3,
        0xE0,
        0x1,
        0xC0,
};
const char Tower_4_graph_[] =
    {
        0x0,
        0xC0,
        0x41,
        0xE0,
        0xA3,
        0xF0,
        0xA4,
        0x8,
        0x44,
        0x8,
        0xD,
        0xBC,
        0xC,
        0xC,
        0xC,
        0x4C,
        0x4,
        0x8,
        0x4,
        0x8,
        0x4,
        0x8,
        0x2,
        0x10,
        0x1,
        0xE0,
        0x7,
        0xF8,
        0xF,
        0xFC,
        0x0,
        0x0,
};

const char MainMenu_graph_[] =
    {
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0x80,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x1,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBC,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x7D,
        0xBD,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0x3D,
        0xBD,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x1,
        0xBD,
        0xBD,
        0x0,
        0xE0,
        0x1F,
        0xC3,
        0x1C,
        0x7F,
        0x8F,
        0xF1,
        0xFC,
        0x38,
        0xC7,
        0xF8,
        0xFE,
        0x1,
        0xBD,
        0xBD,
        0x0,
        0xE0,
        0x1F,
        0xC3,
        0x1C,
        0x7C,
        0x8F,
        0xF1,
        0xCC,
        0x38,
        0xC4,
        0xF8,
        0xFE,
        0x1,
        0xBD,
        0xBD,
        0x0,
        0xE0,
        0x1F,
        0xC3,
        0x9C,
        0x7C,
        0x8F,
        0x1,
        0xCC,
        0x39,
        0xC4,
        0xF8,
        0x9F,
        0x1,
        0xBD,
        0xBD,
        0x0,
        0xE0,
        0x18,
        0xC3,
        0xDC,
        0x7F,
        0x8F,
        0xF1,
        0xFC,
        0x3B,
        0xC7,
        0xF8,
        0x9F,
        0x1,
        0xBD,
        0xBD,
        0x0,
        0xE0,
        0x18,
        0xC3,
        0xFC,
        0x7F,
        0x8F,
        0xF1,
        0xFC,
        0x3F,
        0xC7,
        0xF8,
        0xFF,
        0x1,
        0xBD,
        0xBD,
        0x0,
        0xE0,
        0x1F,
        0xE3,
        0x7C,
        0x1C,
        0xF,
        0xF1,
        0xFC,
        0x3E,
        0xC0,
        0xE0,
        0xFF,
        0x1,
        0xBD,
        0xBD,
        0x0,
        0xE0,
        0x1F,
        0xE3,
        0x3C,
        0x1C,
        0xF,
        0x1,
        0xFC,
        0x3C,
        0xC0,
        0xE0,
        0xFF,
        0x1,
        0xBD,
        0xBD,
        0x0,
        0xFF,
        0x1F,
        0xE3,
        0x3C,
        0x1C,
        0xF,
        0xF1,
        0xCE,
        0x3C,
        0xC0,
        0xE0,
        0xFF,
        0x1,
        0xBD,
        0xBD,
        0x0,
        0x9F,
        0x1F,
        0xE3,
        0x1C,
        0x1C,
        0xF,
        0xF1,
        0xCE,
        0x38,
        0xC0,
        0xE0,
        0xFF,
        0x1,
        0xBD,
        0xBD,
        0x0,
        0x9F,
        0x18,
        0x63,
        0x1C,
        0x1C,
        0xF,
        0xF1,
        0xCE,
        0x38,
        0xC0,
        0xE0,
        0xFF,
        0x1,
        0xBD,
        0xBD,
        0x0,
        0xFF,
        0x18,
        0x63,
        0x1C,
        0x1C,
        0xF,
        0xF1,
        0xCE,
        0x38,
        0xC0,
        0xE0,
        0xFE,
        0x1,
        0xBD,
        0xBD,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x1,
        0xBD,
        0xBD,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x1,
        0xBD,
        0xBD,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xBD,
        0xBC,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xBD,
        0xBE,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x3D,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xF0,
        0x0,
        0x0,
        0x0,
        0x0,
        0xF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xEF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xF7,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xE8,
        0x0,
        0x0,
        0x0,
        0x0,
        0x17,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xEB,
        0xB9,
        0x33,
        0x88,
        0x95,
        0xD7,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xEB,
        0x12,
        0xA9,
        0x11,
        0x5D,
        0x17,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xE9,
        0x93,
        0xB1,
        0x15,
        0xD5,
        0x97,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xEB,
        0x92,
        0xA9,
        0xD,
        0x55,
        0xD7,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xE8,
        0x0,
        0x0,
        0x0,
        0x0,
        0x17,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xEF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xF7,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xF0,
        0x0,
        0x0,
        0x0,
        0x0,
        0xF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xEE,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xFF,
        0xDB,
        0x7F,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xBF,
        0xA5,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFB,
        0xFF,
        0x42,
        0xDF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0x7E,
        0xFF,
        0xEF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xF9,
        0xCF,
        0x56,
        0xDF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFA,
        0x2F,
        0x56,
        0xDF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xE3,
        0xEF,
        0x5F,
        0xDF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xEA,
        0xAF,
        0x40,
        0x5F,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xEB,
        0xEF,
        0x46,
        0x5F,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xE3,
        0xEF,
        0x40,
        0x5F,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0x9F,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xF9,
        0xCE,
        0xFF,
        0xCF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xAF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFE,
        0x3D,
        0x6B,
        0xE7,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0x97,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFA,
        0xD7,
        0xF3,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xAB,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0x95,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xAA,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0x95,
        0x7F,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0xAA,
        0xBF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0x95,
        0x5F,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        0x80,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
        0x1,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
};

const char Button_1_graph_[] =
    {
        0xFE,
        0xFF,
        0xC0,
        0xFD,
        0x7F,
        0xC0,
        0xFB,
        0xBF,
        0xC0,
        0xF7,
        0x7F,
        0xC0,
        0xEA,
        0xBF,
        0xC0,
        0xF5,
        0x5F,
        0x80,
        0xFB,
        0xAF,
        0x0,
        0xFF,
        0xCE,
        0x0,
};

const char Button_2_graph_[] =
    {
        0xFF,
        0xFF,
        0xC0,
        0xBB,
        0x31,
        0xC0,
        0x92,
        0xD6,
        0xC0,
        0xAA,
        0x11,
        0xC0,
        0xBA,
        0xD7,
        0xC0,
        0xBA,
        0xD7,
        0x80,
        0xFF,
        0xFF,
        0x0,
        0xFF,
        0xFE,
        0x0,
};

const char Button_3_graph_[] =
    {
        0xFF,
        0xFF,
        0xC0,
        0x15,
        0x74,
        0x40,
        0xB5,
        0x25,
        0x40,
        0xB5,
        0x54,
        0x40,
        0xB5,
        0x55,
        0xC0,
        0x31,
        0x75,
        0x80,
        0xFF,
        0xFF,
        0x0,
        0xFF,
        0xFE,
        0x0,
};
const char Button_4_graph_[] =
    {
        0xFF,
        0xFF,
        0xC0,
        0xB4,
        0x44,
        0x40,
        0xAD,
        0xDD,
        0x40,
        0x9C,
        0xCC,
        0x40,
        0xAD,
        0xDD,
        0xC0,
        0xB4,
        0x45,
        0x80,
        0xFF,
        0xFF,
        0x0,
        0xFF,
        0xFE,
        0x0,
};
const char Button_5_graph_[] =
    {
        0xFF,
        0xFF,
        0xC0,
        0x88,
        0xD8,
        0xC0,
        0xBD,
        0xAD,
        0xC0,
        0x8D,
        0xAD,
        0xC0,
        0xED,
        0x8D,
        0xC0,
        0x8D,
        0xAD,
        0x80,
        0xFF,
        0xFF,
        0x0,
        0xFF,
        0xFE,
        0x0,
};
const char monster_1_graph_[] =
    {
        0x10,
        0x8,
        0x19,
        0x98,
        0x5B,
        0xDA,
        0x2F,
        0xF4,
        0x6B,
        0xD6,
        0x6D,
        0xB6,
        0xF7,
        0xEF,
        0xDB,
        0xDB,
        0xBC,
        0x3D,
        0x37,
        0xEC,
        0x67,
        0xE6,
        0x73,
        0xCE,
        0x46,
        0x62,
        0xC,
        0x30,
        0x1C,
        0x38,
        0x14,
        0x28,
};
const char Monster_2_graph_[] =
    {
        0x0,
        0x10,
        0x0,
        0x7E,
        0x0,
        0xEE,
        0x0,
        0xFE,
        0x1,
        0xFE,
        0x21,
        0xEA,
        0x11,
        0xF0,
        0x21,
        0xFC,
        0x11,
        0xE0,
        0x10,
        0xF0,
        0x20,
        0x7C,
        0x20,
        0x1E,
        0x3D,
        0xEE,
        0x1F,
        0xFC,
        0x7,
        0xF0,
        0x0,
        0x0,
};
const char Monster_3_graph_[] =
    {
        0x0,
        0x0,
        0x7,
        0x70,
        0xD,
        0xD8,
        0xD,
        0xD8,
        0xD,
        0xD8,
        0xF,
        0xFC,
        0xE,
        0x3C,
        0xF,
        0xFC,
        0x7,
        0xF8,
        0x0,
        0x0,
        0x3,
        0xF0,
        0x0,
        0x8,
        0xB,
        0xF0,
        0x2,
        0x10,
        0x0,
        0x0,
        0x0,
        0x0,
};
const char Monster_4_graph_[] =
    {
        0x0,
        0x0,
        0x1C,
        0x1C,
        0x3,
        0xE0,
        0x7,
        0xF8,
        0x3C,
        0xCC,
        0x1F,
        0xF8,
        0x1F,
        0xF8,
        0x1F,
        0xF8,
        0x5,
        0x50,
        0x0,
        0x4,
        0x1D,
        0xFC,
        0x1D,
        0xFC,
        0x1F,
        0xF8,
        0x17,
        0xF8,
        0x4,
        0x10,
        0x0,
        0x0,
};
const char Monster_5_graph_[] =
    {
        0x0,
        0x0,
        0x7,
        0xF0,
        0xE,
        0x8,
        0xC,
        0x24,
        0x1C,
        0xA4,
        0x1C,
        0x84,
        0x3C,
        0x4,
        0x34,
        0x4,
        0x26,
        0x8,
        0x3,
        0xF0,
        0x4,
        0x8,
        0x3,
        0xF0,
        0x3,
        0xF4,
        0xB,
        0xF0,
        0x1,
        0x10,
        0x1,
        0x10,
};

int Bkey_n_IsKeyDown(int keycode)
{
    int kcode1 = 0, kcode2 = 0;
    int gcode1, gcode2;
    short unused = 0;

    switch (keycode)
    {
    case KEY_CHAR_0:
        GETCODE(7, 2);
        break;
    case KEY_CHAR_1:
        GETCODE(7, 3);
        break;
    case KEY_CHAR_2:
        GETCODE(6, 3);
        break;
    case KEY_CHAR_3:
        GETCODE(5, 3);
        break;
    case KEY_CHAR_4:
        GETCODE(7, 4);
        break;
    case KEY_CHAR_5:
        GETCODE(6, 4);
        break;
    case KEY_CHAR_6:
        GETCODE(5, 4);
        break;
    case KEY_CHAR_7:
        GETCODE(7, 5);
        break;
    case KEY_CHAR_8:
        GETCODE(6, 5);
        break;
    case KEY_CHAR_9:
        GETCODE(5, 5);
        break;
    case KEY_CHAR_DP:
        GETCODE(6, 2);
        break;
    case KEY_CHAR_EXP:
        GETCODE(5, 2);
        break;
    case KEY_CHAR_PMINUS:
        GETCODE(4, 2);
        break;
    case KEY_CHAR_PLUS:
        GETCODE(4, 3);
        break;
    case KEY_CHAR_MINUS:
        GETCODE(3, 3);
        break;
    case KEY_CHAR_MULT:
        GETCODE(4, 4);
        break;
    case KEY_CHAR_DIV:
        GETCODE(3, 4);
        break;
    case KEY_CTRL_EXE:
        GETCODE(3, 2);
        break;
    case KEY_CTRL_DEL:
        GETCODE(4, 5);
        break;
    case KEY_CTRL_AC:
        GETCODE(1, 1);
        break;
    case KEY_CHAR_FRAC:
        GETCODE(7, 6);
        break;
    case KEY_CTRL_FD:
        GETCODE(6, 6);
        break;
    case KEY_CHAR_LPAR:
        GETCODE(5, 6);
        break;
    case KEY_CHAR_RPAR:
        GETCODE(4, 6);
        break;
    case KEY_CHAR_COMMA:
        GETCODE(3, 6);
        break;
    case KEY_CHAR_STORE:
        GETCODE(2, 6);
        break;
    case KEY_CTRL_XTT:
        GETCODE(7, 7);
        break;
    case KEY_CHAR_LOG:
        GETCODE(6, 7);
        break;
    case KEY_CHAR_LN:
        GETCODE(5, 7);
        break;
    case KEY_CHAR_SIN:
        GETCODE(4, 7);
        break;
    case KEY_CHAR_COS:
        GETCODE(3, 7);
        break;
    case KEY_CHAR_TAN:
        GETCODE(2, 7);
        break;
    case KEY_CHAR_SQUARE:
        GETCODE(6, 8);
        break;
    case KEY_CHAR_POW:
        GETCODE(5, 8);
        break;
    case KEY_CTRL_EXIT:
        GETCODE(4, 8);
        break;
    case KEY_CTRL_SHIFT:
        GETCODE(7, 9);
        break;
    case KEY_CTRL_ALPHA:
        GETCODE(7, 8);
        break;
    case KEY_CTRL_OPTN:
        GETCODE(6, 9);
        break;
    case KEY_CTRL_VARS:
        GETCODE(5, 9);
        break;
    case KEY_CTRL_MENU:
        GETCODE(4, 9);
        break;
    case KEY_CTRL_UP:
        GETCODE(2, 9);
        break;
    case KEY_CTRL_DOWN:
        GETCODE(3, 8);
        break;
    case KEY_CTRL_LEFT:
        GETCODE(3, 9);
        break;
    case KEY_CTRL_RIGHT:
        GETCODE(2, 8);
        break;
    case KEY_CTRL_F1:
        GETCODE(7, 10);
        break;
    case KEY_CTRL_F2:
        GETCODE(6, 10);
        break;
    case KEY_CTRL_F3:
        GETCODE(5, 10);
        break;
    case KEY_CTRL_F4:
        GETCODE(4, 10);
        break;
    case KEY_CTRL_F5:
        GETCODE(3, 10);
        break;
    case KEY_CTRL_F6:
        GETCODE(2, 10);
        break;

    default:
        return 0;
    }

    if (Bkey_GetKeyWait(&kcode1, &kcode2, KEYWAIT_HALTOFF_TIMEROFF, 0, 0, &unused) == KEYREP_KEYEVENT)
    {
        if ((kcode1 == gcode1) && (kcode2 == gcode2))
            return 1;
    }
    return 0;
}
void Data_Match(LPTOWERPLACE Need_Match, LPTOWER Tower_data, LPPOSITION Tower_Position)
{
    Need_Match->Place_Tower->id = Tower_data->id;
    Need_Match->Place_Tower->Attack = Tower_data->Attack;
    Need_Match->Place_Tower->Attack_Frequency = Tower_data->Attack_Frequency;
    Need_Match->Place_Tower->Attack_Range = Tower_data->Attack_Range;
    Need_Match->Place_Tower->Tower_Level = Tower_data->Tower_Level;
    Need_Match->position->x = Tower_Position->x;
    Need_Match->position->y = Tower_Position->y;
}

void printf_xy(int x, int y, int mode, const char *format, ...)
{
    static char buff[200];
    va_list args;
    int i;
    va_start(args, format);
    i = vsprintf(buff, format, args);
    va_end(args);
    buff[i] = '\0';
    PrintXY(x, y, (const unsigned char *)buff, mode);
    Bdisp_PutDisp_DD();
}
void printf_pop_xy(int x, int y, const char *format, ...)
{
    static char buff[200];
    va_list args;
    int i;
    va_start(args, format);
    i = vsprintf(buff, format, args);
    va_end(args);
    buff[i] = '\0';
    locate(x, y);
    Print((const unsigned char *)buff);
    Bdisp_PutDisp_DD();
}

int my_atoi(const char *str)
{
    int n = 0;
    while (*str != '\0')
    {
        n = n * 10 + (*str - '0');
        str++;
    }
    return n;
}

void draw_picture(int x, int y, int width, int height, int kind, int mod, unsigned char *pGraph)
{
    DISPGRAPH dg;
    dg.x = x;
    dg.y = y;
    dg.GraphData.width = width;
    dg.GraphData.height = height;
    dg.GraphData.pBitmap = pGraph;
    dg.WriteModify = mod;
    dg.WriteKind = kind;
    Bdisp_WriteGraph_VRAM(&dg);
}

void area_clear(int left, int top, int right, int bottom, int sel)
{
    DISPBOX box;
    box.left = left;
    box.top = top;
    box.right = right;
    box.bottom = bottom;
    if (sel != 1)
        Bdisp_AreaClr_VRAM(&box);
    if (sel != 0)
    {
        Bdisp_DrawLineVRAM(box.left, box.top, box.right, box.top);
        Bdisp_DrawLineVRAM(box.left, box.bottom, box.right, box.bottom);
        Bdisp_DrawLineVRAM(box.left, box.top, box.left, box.bottom);
        Bdisp_DrawLineVRAM(box.right, box.top, box.right, box.bottom);
    }
}

void EnterGame()
{
    // Bdisp_AllClr_DDVRAM();
    Bdisp_AllClr_VRAM();
    draw_picture(0, 0, 128, 64, 1, 1, MainMenu_graph_);
    Bdisp_PutDisp_DD();
}
void Map_Initialization(int *Map_Array, LPPOSITION Current_Screen, LPPOSITION last_position, int numOfCurrent)
{
    int i, j;
    int screen_x = 0, screen_y = 0;
    for (i = Current_Screen->y; i < Current_Screen->y + 4; i++)
    {
        for (j = Current_Screen->x; j < Current_Screen->x + 8; j++)
        {
            switch (Map_Array[i * 37 + j])
            {
            case 1:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Tile_Default_graph_);
                break;
            case 2:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, spawn_door_graph_);
                break;
            case 3:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, base_graph_);
                break;
            case 4:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, check_point_1_graph_);
                break;
            case 5:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, check_point_2_graph_);
                break;
            case 6:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, check_point_3_graph_);
                break;
            case 7:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, check_point_4_graph_);
                break;
            case 8:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, check_point_5_graph_);
                break;
            case 49:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Wall_graph_);
                break;
            case 50:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Tower_Default_graph_);
                break;
            case 51:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Tower_1_graph_);
                break;
            case 52:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Tower_2_graph_);
                break;
            case 53:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Tower_3_graph_);
                break;
            case 54:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Tower_4_graph_);
                break;
            }
            screen_x += 16;
        }
        screen_x = 0;
        screen_y += 16;
    }
    draw_picture(last_position->x, last_position->y, 8, 8, 2, 1, cursor_graph_);
    if (numOfCurrent < 5)
    {
        draw_picture(2, 55, 20, 8, 1, 1, Button_1_graph_);
    }
    else
    {
        draw_picture(2, 55, 20, 8, 1, 1, Button_4_graph_);
    }
    draw_picture(22, 55, 20, 8, 1, 1, Button_2_graph_);
    draw_picture(42, 55, 20, 8, 1, 1, Button_3_graph_);
    draw_picture(82, 55, 20, 8, 1, 1, Button_5_graph_);
}

void Battle_Map(int *Map_Array, LPPOSITION Current_Screen, LPPOSITION last_position, LPMONSTERLIVE Monster_LiveMonster[], int numOfMonster)
{
    int i, j, MonsterIndex;
    int CurrentPosition_x, CurrentPosition_y;
    int screen_x = 0, screen_y = 0;
    int direction_x = 0, direction_y = 0;
    MonsterIndex = 0;
    for (i = Current_Screen->y; i < Current_Screen->y + 4; i++)
    {
        for (j = Current_Screen->x; j < Current_Screen->x + 8; j++)
        {
            switch (Map_Array[i * 37 + j])
            {
            case 1:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Tile_Default_graph_);
                break;
            case 2:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, spawn_door_graph_);
                break;
            case 3:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, base_graph_);
                break;
            case 4:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, check_point_1_graph_);
                break;
            case 5:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, check_point_2_graph_);
                break;
            case 6:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, check_point_3_graph_);
                break;
            case 7:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, check_point_4_graph_);
                break;
            case 8:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, check_point_5_graph_);
                break;
            case 49:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Wall_graph_);
                break;
            case 50:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Tower_Default_graph_);
                break;
            case 51:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Tower_1_graph_);
                break;
            case 52:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Tower_2_graph_);
                break;
            case 53:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Tower_3_graph_);
                break;
            case 54:
                draw_picture(screen_x, screen_y, 16, 16, 1, 1, Tower_4_graph_);
                break;
            }
            screen_x += 16;
        }
        screen_x = 0;
        screen_y += 16;
    }
    screen_x = 0;
    screen_y = 0;

    for (MonsterIndex = 0; MonsterIndex < numOfMonster; MonsterIndex++)
    {
        direction_x = Monster_LiveMonster[MonsterIndex]->target_position->x - Monster_LiveMonster[MonsterIndex]->position->x;
        direction_y = Monster_LiveMonster[MonsterIndex]->target_position->y - Monster_LiveMonster[MonsterIndex]->position->y;
        for (i = Current_Screen->y; i < Current_Screen->y + 4; i++)
        {
            for (j = Current_Screen->x; j < Current_Screen->x + 8; j++)
            {
                if (Monster_LiveMonster[MonsterIndex]->position->x == i && Monster_LiveMonster[MonsterIndex]->position->y == j)
                {
                    switch (Monster_LiveMonster[MonsterIndex]->Monster_Live->id)
                    {
                    case 100:
                        draw_picture(screen_x + (Monster_LiveMonster[MonsterIndex]->Move_Distance) * direction_y, screen_y + (Monster_LiveMonster[MonsterIndex]->Move_Distance) * direction_x, 16, 16, 2, 1, monster_1_graph_);
                        break;
                    case 101:
                        draw_picture(screen_x + (Monster_LiveMonster[MonsterIndex]->Move_Distance) * direction_y, screen_y + (Monster_LiveMonster[MonsterIndex]->Move_Distance) * direction_x, 16, 16, 2, 1, Monster_2_graph_);
                        break;
                    case 102:
                        draw_picture(screen_x + (Monster_LiveMonster[MonsterIndex]->Move_Distance) * direction_y, screen_y + (Monster_LiveMonster[MonsterIndex]->Move_Distance) * direction_x, 16, 16, 2, 1, Monster_3_graph_);
                        break;
                    case 103:
                        draw_picture(screen_x + (Monster_LiveMonster[MonsterIndex]->Move_Distance) * direction_y, screen_y + (Monster_LiveMonster[MonsterIndex]->Move_Distance) * direction_x, 16, 16, 2, 1, Monster_4_graph_);
                        break;
                    case 104:
                        draw_picture(screen_x + (Monster_LiveMonster[MonsterIndex]->Move_Distance) * direction_y, screen_y + (Monster_LiveMonster[MonsterIndex]->Move_Distance) * direction_x, 16, 16, 2, 1, Monster_5_graph_);
                        break;

                    default:
                        break;
                    }
                }
                screen_x += 16;
            }
            screen_x = 0;
            screen_y += 16;
        }
        screen_x = 0;
        screen_y = 0;
    }
}

void Cursor_Move(unsigned int key, LPPOSITION last_position, LPPOSITION Screen_position)
{

    switch (key)
    {
    case KEY_CTRL_UP:
        if (last_position->y >= 8)
        {
            last_position->y -= 8;
        }
        else
        {
            if (Screen_position->y > 0)
            {
                Screen_position->y -= 1;
            }
        }
        break;
    case KEY_CTRL_DOWN:
        if (last_position->y <= 55)
        {

            last_position->y += 8;
        }
        else
        {
            if (Screen_position->y < 33)
            {
                Screen_position->y += 1;
            }
        }
        break;
    case KEY_CTRL_LEFT:
        if (last_position->x >= 8)
        {
            last_position->x -= 8;
        }
        else
        {
            if (Screen_position->x > 0)
            {
                Screen_position->x -= 1;
            }
        }
        break;
    case KEY_CTRL_RIGHT:
        if (last_position->x <= 119)
        {
            last_position->x += 8;
        }
        else
        {
            if (Screen_position->x < 29)
            {
                Screen_position->x += 1;
            }
        }
        break;
    }
}

void Screen_Move(LPPOSITION Screen_position)
{
    if (Bkey_n_IsKeyDown(KEY_CTRL_UP))
    {
        if (Screen_position->y > 0)
        {
            Screen_position->y -= 1;
        }
    }
    else if (Bkey_n_IsKeyDown(KEY_CTRL_DOWN))
    {
        if (Screen_position->y < 33)
        {
            Screen_position->y += 1;
        }
    }
    else if (Bkey_n_IsKeyDown(KEY_CTRL_LEFT))
    {
        if (Screen_position->x > 0)
        {
            Screen_position->x -= 1;
        }
    }
    else if (Bkey_n_IsKeyDown(KEY_CTRL_RIGHT))
    {

        if (Screen_position->x < 29)
        {
            Screen_position->x += 1;
        }
    }
}

void Tower_Place(unsigned int key, LPPOSITION Cursor_Position, LPPOSITION Screen_Position, int *Map, LPTOWER Tower_DataBase[], int Tower_DbSize, LPTOWERPLACE Tower_PlaceTower[], LPTOWERPLACE Tower_Buffer[5], int *numOfPlace, int *numOfCurrent, int *Direction, int *numOfDirection, int *IsPlaceOver)
{
    int i, j, id, temp_MapId;
    int x, y;
    temp_MapId = -1;
    srand((unsigned int)RTC_GetTicks());
    x = Screen_Position->y + (Cursor_Position->y / 16);
    y = Screen_Position->x + (Cursor_Position->x / 16);
    if (key == KEY_CTRL_F1)
    {
        if (*numOfCurrent < 5)
        {

            if (Map[x * 37 + y] < 49)
            {
                id = rand() % 5 + 50;
                temp_MapId = Map[x * 37 + y];
                Map[x * 37 + y] = id;
                if (Check_Path(Map, Direction, numOfDirection))
                {

                    Tower_Buffer[*numOfCurrent] = (LPTOWERPLACE)malloc(sizeof(TOWERPLACE));
                    Tower_Buffer[*numOfCurrent]->Place_Tower = (LPTOWER)malloc(sizeof(Tower));
                    Tower_Buffer[*numOfCurrent]->position = (LPPOSITION)malloc(sizeof(POSITION));
                    Tower_Buffer[*numOfCurrent]->Place_Tower->id = id;
                    Tower_Buffer[*numOfCurrent]->position->x = x;
                    Tower_Buffer[*numOfCurrent]->position->y = y;

                    for (i = 0; i < Tower_DbSize; i++)
                    {
                        if (Tower_DataBase[i]->id == Tower_Buffer[*numOfCurrent]->Place_Tower->id)
                        {
                            Data_Match(Tower_Buffer[*numOfCurrent], Tower_DataBase[i], Tower_Buffer[*numOfCurrent]->position);
                            break;
                        }
                    }
                    *numOfCurrent = *numOfCurrent + 1;
                }
                else
                {
                    PopUpWin(4);
                    printf_pop_xy(5, 2, "Cannot block");
                    printf_pop_xy(5, 3, "every line");
                    printf_pop_xy(5, 4, "Press [EXE] key");
                    do
                    {
                        GetKey(&key);
                    } while (key != KEY_CTRL_EXE);
                    Map[x * 37 + y] = temp_MapId;
                    // Bdisp_AllClr_DDVRAM();
                    Bdisp_AllClr_VRAM();
                }
            }
            else
            {
                PopUpWin(4);
                printf_pop_xy(5, 2, "wrong position");
                printf_pop_xy(3, 3, "plz select empty");
                printf_pop_xy(5, 4, "Press [EXE] key");
                do
                {
                    GetKey(&key);
                } while (key != KEY_CTRL_EXE);
                // Bdisp_AllClr_DDVRAM();
                Bdisp_AllClr_VRAM();
            }
        }
        else
        {
            for (i = 0; i < 5; i++)
            {
                if (Tower_Buffer[i]->position->x == x && Tower_Buffer[i]->position->y == y)
                {
                    Tower_PlaceTower[*numOfPlace] = (LPTOWERPLACE)malloc(sizeof(TOWERPLACE));
                    Tower_PlaceTower[*numOfPlace]->Place_Tower = (LPTOWER)malloc(sizeof(Tower));
                    Tower_PlaceTower[*numOfPlace]->position = (LPPOSITION)malloc(sizeof(POSITION));
                    Data_Match(Tower_PlaceTower[*numOfPlace], Tower_Buffer[i]->Place_Tower, Tower_Buffer[i]->position);
                    *numOfPlace = *numOfPlace + 1;
                    break;
                }
            }
            if (i < 5)
            {

                for (j = 0; j < 5; j++)
                {
                    if (j == i)
                    {
                        continue;
                    }
                    else
                    {
                        x = Tower_Buffer[j]->position->x;
                        y = Tower_Buffer[j]->position->y;
                        Map[x * 37 + y] = 49;
                    }
                }

                for (i = 0; i < *numOfCurrent; i++)
                {
                    free_Tower(Tower_Buffer, numOfCurrent, i);
                }
                *numOfCurrent = 0;
                *IsPlaceOver = 1;
            }
            else
            {
                PopUpWin(4);
                printf_pop_xy(4, 2, "wrong position");
                printf_pop_xy(3, 3, "choose right tower");
                printf_pop_xy(5, 4, "Press [EXE] key");
                do
                {
                    GetKey(&key);
                } while (key != KEY_CTRL_EXE);
                // Bdisp_AllClr_DDVRAM();
                Bdisp_AllClr_VRAM();
            }
        }
    }
}

void Open_Map(unsigned int key, int *Map)
{
    unsigned int i, j;
    if (key == KEY_CTRL_F2)
    {
        // Bdisp_AllClr_DDVRAM();
        Bdisp_AllClr_VRAM();
        area_clear(43, 11, 84, 52, 1); // draw square frame
        for (i = 0; i < 37; i++)
        {
            for (j = 0; j < 37; j++)
            {
                if (Map[i * 37 + j] >= 49)
                {
                    draw_picture(j + 45, i + 13, 1, 1, 1, 1, POINT);
                }
            }
        }

        draw_picture(22, 55, 20, 8, 1, 1, Button_2_graph_);
        do
        {
            GetKey(&key);
        } while (key != KEY_CTRL_EXIT);
    }
}

void Jump_View(unsigned int key, LPPOSITION Screen_Position)
{
    char row[10], col[10];
    char *Row, *Col;
    int rowNum, colNum;
    int x, y, i;

    Row = row;
    Col = col;
    rowNum = 0;
    colNum = 0;
    // initialize array
    memset(Row, 0, sizeof(char) * 10);
    memset(Col, 0, sizeof(char) * 10);
    // Bdisp_AllClr_DDVRAM();
    Bdisp_AllClr_VRAM();
    draw_picture(42, 55, 20, 8, 1, 1, Button_3_graph_);

    if (key == KEY_CTRL_F3)
    {

        while (1)
        {
            locate(1, 1);
            Print((unsigned char *)"Please enter the numb");
            locate(1, 2);
            Print((unsigned char *)"er of rows:(0~33)");

            do
            {
                GetKey(&key);
                if (rowNum < 10)
                {
                    if (key >= KEY_CHAR_0 && key <= KEY_CHAR_9)
                    {
                        row[rowNum] = GetNumber(key);
                        rowNum++;
                        locate(21 - rowNum + 1, 3);
                        Print(Row);
                    }
                    else if (key == KEY_CTRL_AC)
                    {
                        memset(Row, 0, sizeof(char) * 10);
                        rowNum = 0;
                        area_clear(0, 16, 127, 24, 0);
                    }
                }
            } while (key != KEY_CTRL_EXE);

            x = my_atoi(Row);

            if (x >= 0 && x <= 33)
            {
                break;
            }
            else
            {
                PopUpWin(3);
                locate(7, 3);
                Print((unsigned char *)"Wrong number");
                locate(5, 5);
                Print((unsigned char *)"Press [0] key");
                do
                {
                    GetKey(&key);
                } while (key != KEY_CHAR_0);
                memset(Row, 0, sizeof(char) * 10);
                rowNum = 0;
            }
            x = -1;
            // Bdisp_AllClr_DDVRAM();
            Bdisp_AllClr_VRAM();
            draw_picture(42, 55, 20, 8, 1, 1, Button_3_graph_);
        }
        // Bdisp_AllClr_DDVRAM();
        Bdisp_AllClr_VRAM();
        draw_picture(42, 55, 20, 8, 1, 1, Button_3_graph_);
        while (1)
        {
            locate(1, 1);
            Print((unsigned char *)"Please enter the numb");
            locate(1, 2);
            Print((unsigned char *)"er of cols:(0~29)");
            do
            {
                GetKey(&key);
                if (colNum < 10)
                {
                    if (key >= KEY_CHAR_0 && key <= KEY_CHAR_9)
                    {
                        col[colNum] = GetNumber(key);
                        colNum++;
                        locate(21 - colNum + 1, 3);
                        Print(Col);
                    }
                    else if (key == KEY_CTRL_AC)
                    {
                        memset(Col, 0, sizeof(char) * 10);
                        colNum = 0;
                        area_clear(0, 16, 127, 24, 0);
                    }
                }
            } while (key != KEY_CTRL_EXE);

            y = my_atoi(Col);

            if (y >= 0 && y <= 29)
            {
                break;
            }
            else
            {
                PopUpWin(3);
                locate(7, 3);
                Print((unsigned char *)"Wrong number");
                locate(5, 5);
                Print((unsigned char *)"Press [0] key");
                do
                {
                    GetKey(&key);
                } while (key != KEY_CHAR_0);
                memset(Col, 0, sizeof(char) * 10);
                colNum = 0;
            }
            y = -1;
            // Bdisp_AllClr_DDVRAM();
            Bdisp_AllClr_VRAM();
            draw_picture(42, 55, 20, 8, 1, 1, Button_3_graph_);
        }
        Screen_Position->x = y;
        Screen_Position->y = x;
    }
}

int Tower_LevelUp(LPTOWERPLACE Tower_PlaceTower[], int *numOfPlace, LPTOWERPLACE target_tower, int *Map)
{
    int i, counters;
    int temp_index[2];
    LPTOWERPLACE LevelUp_Buffer[2];
    counters = 0;
    temp_index[0] = -1;
    temp_index[1] = -1;
    for (i = 0; i < *numOfPlace; i++)
    {
        if (Tower_PlaceTower[i]->Place_Tower->id == target_tower->Place_Tower->id && Tower_PlaceTower[i]->Place_Tower->Tower_Level == target_tower->Place_Tower->Tower_Level)
        {
            if (Tower_PlaceTower[i]->position->x != target_tower->position->x && Tower_PlaceTower[i]->position->y != target_tower->position->x)
            {
                temp_index[counters] = i;
                LevelUp_Buffer[counters] = Tower_PlaceTower[i];
                counters++;
            }
        }
        if (counters == 2)
        {
            break;
        }
    }
    if (counters == 2)
    {
        Map[37 * LevelUp_Buffer[0]->position->x + LevelUp_Buffer[0]->position->y] = 49;
        Map[37 * LevelUp_Buffer[1]->position->x + LevelUp_Buffer[1]->position->y] = 49;
        free_Tower(Tower_PlaceTower, numOfPlace, temp_index[0]);
        free_Tower(Tower_PlaceTower, numOfPlace, temp_index[1]);
        target_tower->Place_Tower->Tower_Level += 1;
        return 1;
    }
    else
    {
        return 0;
    }
}

void Check_Status(unsigned int key, LPPOSITION Cursor_Position, LPPOSITION Screen_Position, int *Map, LPTOWERPLACE Tower_PlaceTower[], LPTOWER Tower_Database[], int numOfTower, int Tower_DbSize)
{
    int x, y;
    int Tower_id;
    int i;
    if (key == KEY_CTRL_F5)
    {
        // Bdisp_AllClr_DDVRAM();
        Bdisp_AllClr_VRAM();
        x = Screen_Position->y + (Cursor_Position->y / 16);
        y = Screen_Position->x + (Cursor_Position->x / 16);
        Tower_id = Map[x * 37 + y];
        if (numOfTower)
        {
            for (i = 0; i < numOfTower; i++)
            {
                if (Tower_PlaceTower[i]->position->x == x && Tower_PlaceTower[i]->position->y == y)
                {
                    printf_pop_xy(1, 1, "Tower Level:%d", Tower_PlaceTower[i]->Place_Tower->Tower_Level);
                    printf_pop_xy(1, 2, "ATTACK:%f", Tower_PlaceTower[i]->Place_Tower->Attack);
                    printf_pop_xy(1, 3, "Attack Frequency:%f", Tower_PlaceTower[i]->Place_Tower->Attack_Frequency);
                    printf_pop_xy(1, 4, "Attack Range:%d", Tower_PlaceTower[i]->Place_Tower->Attack_Range);
                    Tower_LevelUp(Tower_PlaceTower, &numOfTower, Tower_PlaceTower[i], Map);
                    break;
                }
            }
        }
        if (i == numOfTower || !numOfTower)
        {
            for (i = 0; i < Tower_DbSize; i++)
            {
                if (Tower_Database[i]->id == Tower_id)
                {
                    printf_pop_xy(1, 1, "Tower Level:%d", Tower_Database[i]->Tower_Level);
                    printf_pop_xy(1, 2, "ATTACK:%f", Tower_Database[i]->Attack);
                    printf_pop_xy(1, 3, "Attack Frequency:%f", Tower_Database[i]->Attack_Frequency);
                    printf_pop_xy(1, 4, "Attack Range:%d", Tower_Database[i]->Attack_Range);
                    break;
                }
            }
        }

        draw_picture(82, 55, 20, 8, 1, 1, Button_5_graph_);
        do
        {
            GetKey(&key);
        } while (key != KEY_CTRL_EXIT);
    }
}

int Check_Path(int *Map, int *Direction, int *numOfDirection)
{
    LPSTACK OpenList;
    LPSTACK CloseList;
    int tempDirection[4096];
    int tempNumOfDirection;
    int i, j;

    tempNumOfDirection = 0;
    *numOfDirection = 0;

    OpenList = (LPSTACK)malloc(sizeof(Stack));
    OpenList->next = NULL;
    CloseList = (LPSTACK)malloc(sizeof(Stack));
    CloseList->next = NULL;

    if (Astar(2, 4, 18, 4, 37, Map, OpenList, CloseList, tempDirection, &tempNumOfDirection))
    {
        i = 0;
        j = 0;
        ListClear(OpenList);
        ListClear(CloseList);
        for (i = *numOfDirection; i < tempNumOfDirection + *numOfDirection; i++)
        {
            Direction[i] = tempDirection[j];
            j++;
        }
        *numOfDirection = tempNumOfDirection + *numOfDirection;
    }
    else
    {
        return 0;
    }
    if (Astar(18, 4, 18, 32, 37, Map, OpenList, CloseList, tempDirection, &tempNumOfDirection))
    {
        i = 0;
        j = 0;
        ListClear(OpenList);
        ListClear(CloseList);
        for (i = *numOfDirection; i < tempNumOfDirection + *numOfDirection; i++)
        {
            Direction[i] = tempDirection[j];
            j++;
        }
        *numOfDirection = tempNumOfDirection + *numOfDirection;
    }
    else
    {
        return 0;
    }
    if (Astar(18, 32, 4, 32, 37, Map, OpenList, CloseList, tempDirection, &tempNumOfDirection))
    {
        i = 0;
        j = 0;
        ListClear(OpenList);
        ListClear(CloseList);
        for (i = *numOfDirection; i < tempNumOfDirection + *numOfDirection; i++)
        {
            Direction[i] = tempDirection[j];
            j++;
        }
        *numOfDirection = tempNumOfDirection + *numOfDirection;
    }
    else
    {
        return 0;
    }
    if (Astar(4, 32, 4, 18, 37, Map, OpenList, CloseList, tempDirection, &tempNumOfDirection))
    {
        i = 0;
        j = 0;
        ListClear(OpenList);
        ListClear(CloseList);
        for (i = *numOfDirection; i < tempNumOfDirection + *numOfDirection; i++)
        {
            Direction[i] = tempDirection[j];
            j++;
        }
        *numOfDirection = tempNumOfDirection + *numOfDirection;
    }
    else
    {
        return 0;
    }
    if (Astar(4, 18, 32, 18, 37, Map, OpenList, CloseList, tempDirection, &tempNumOfDirection))
    {
        i = 0;
        j = 0;
        ListClear(OpenList);
        ListClear(CloseList);
        for (i = *numOfDirection; i < tempNumOfDirection + *numOfDirection; i++)
        {
            Direction[i] = tempDirection[j];
            j++;
        }
        *numOfDirection = tempNumOfDirection + *numOfDirection;
    }
    else
    {
        return 0;
    }
    if (Astar(32, 18, 32, 34, 37, Map, OpenList, CloseList, tempDirection, &tempNumOfDirection))
    {
        i = 0;
        j = 0;
        ListClear(OpenList);
        ListClear(CloseList);
        for (i = *numOfDirection; i < tempNumOfDirection + *numOfDirection; i++)
        {
            Direction[i] = tempDirection[j];
            j++;
        }
        *numOfDirection = tempNumOfDirection + *numOfDirection;
    }
    else
    {
        return 0;
    }
    return 1;
}

void Tower_Attack(LPTOWERPLACE Tower_PlaceTower[], int numOfTower, LPMONSTERLIVE Monster_LiveMonster[], int numOfMonster)
{
    int i, j;
    for (i = 0; i < numOfTower; i++)
    {
        for (j = 0; j < numOfMonster; j++)
        {
            if (abs(Tower_PlaceTower[i]->position->x - Monster_LiveMonster[j]->target_position->x) <= (Tower_PlaceTower[i]->Place_Tower->Attack_Range / 2) && abs(Tower_PlaceTower[i]->position->y - Monster_LiveMonster[j]->target_position->y) <= (Tower_PlaceTower[i]->Place_Tower->Attack_Range / 2))
            {
                Monster_LiveMonster[j]->Monster_Live->damage += Tower_PlaceTower[i]->Place_Tower->Attack * Tower_PlaceTower[i]->Place_Tower->Tower_Level;
                break;
            }
            if (abs(Tower_PlaceTower[i]->position->x - Monster_LiveMonster[j]->position->x) <= (Tower_PlaceTower[i]->Place_Tower->Attack_Range / 2) && abs(Tower_PlaceTower[i]->position->y - Monster_LiveMonster[j]->position->y) <= (Tower_PlaceTower[i]->Place_Tower->Attack_Range / 2))
            {
                Monster_LiveMonster[j]->Monster_Live->damage += Tower_PlaceTower[i]->Place_Tower->Attack * Tower_PlaceTower[i]->Place_Tower->Tower_Level;
                break;
            }
        }
    }
}

int free_Tower(LPTOWERPLACE Tower_PlaceTower[], int *numOfTower, int needFree_index)
{
    int i;
    LPTOWERPLACE Tower_temp;

    if (needFree_index >= *numOfTower)
    {
        return 0;
    }
    Tower_temp = Tower_PlaceTower[needFree_index];
    if (needFree_index != *numOfTower - 1)
    {
        for (i = needFree_index; i  < *numOfTower; i++)
        {
            Tower_PlaceTower[i] = Tower_PlaceTower[i + 1];
        }
    }
    free(Tower_temp->Place_Tower);
    free(Tower_temp->position);
    free(Tower_temp);
    *numOfTower -= 1;
    return 1;
}
int free_Monster(LPMONSTERLIVE Monster_LiveMonster[], int *numOfMonster, int needFree_index)
{
    int i;
    LPMONSTERLIVE Monster_temp;

    if (needFree_index >= *numOfMonster)
    {
        return 0;
    }
    Monster_temp = Monster_LiveMonster[needFree_index];
    if (needFree_index != *numOfMonster - 1)
    {
        for (i = needFree_index; i  < *numOfMonster; i++)
        {
            Monster_LiveMonster[i] = Monster_LiveMonster[i + 1];
        }
    }
    free(Monster_temp->Monster_Live);
    free(Monster_temp->position);
    free(Monster_temp->target_position);
    free(Monster_temp);
    *numOfMonster -= 1;
    return 1;
}

char GetNumber(unsigned int key)
{
    switch (key)
    {
    case KEY_CHAR_0:
        return '0';

    case KEY_CHAR_1:
        return '1';

    case KEY_CHAR_2:
        return '2';

    case KEY_CHAR_3:
        return '3';

    case KEY_CHAR_4:
        return '4';

    case KEY_CHAR_5:
        return '5';

    case KEY_CHAR_6:
        return '6';

    case KEY_CHAR_7:
        return '7';

    case KEY_CHAR_8:
        return '8';

    case KEY_CHAR_9:
        return '9';
    }
}
