#ifndef __FFUN_H__
#define __FFUN_H__

#include "fxlib.h"

FONTCHARACTER *char_to_font(const char *cFileName, FONTCHARACTER *fFileName);
int read_text_file(char **text,const char *fFileName);

#endif