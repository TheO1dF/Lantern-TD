#include "fxlib.h"
#include "stdlib.h"
#include "ffun.h"

FONTCHARACTER *char_to_font(const char *cFileName, FONTCHARACTER *fFileName)
{
    int i, len = strlen(cFileName);
    for (i = 0; i < len; ++i)
        fFileName[i] = cFileName[i];
    fFileName[i] = 0;
    return fFileName;
}

int read_text_file(char **text,const char *fFileName)
{
    int file_handle;
    int len;
    FONTCHARACTER font_file_name[32];
    char_to_font(fFileName, font_file_name);
    file_handle = Bfile_OpenFile(font_file_name, _OPENMODE_READ);
    if (file_handle < 0)
        return -1;
    len = Bfile_GetFileSize(file_handle);
    *text = (char *)malloc(len + 1);
    if (*text == 0)
        return 0;
    Bfile_ReadFile(file_handle, *text, len, 0);
    Bfile_CloseFile(file_handle);
    (*text)[len] = '\0';
    return 1;
}
