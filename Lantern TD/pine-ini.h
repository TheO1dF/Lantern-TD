#ifndef _PINE_INI_H_
#define _PINE_INI_H_

#include <string.h>

#ifndef NULL
#define NULL ((void *) 0)
#endif

typedef int PINE_BOOL;
#define PINE_TRUE   1
#define PINE_FALSE  0

//
// * How many parameters in section
//
#define PINE_INI_MAX_NUM_PARAMETERS     25

//
// * How many sections in ini file
//
#define PINE_INI_MAX_NUM_SECTIONS       25

//
// * The maximum length of token in ini
//
#define PINE_INI_LINE_MAX_LEN          150

//
// * A single parameter in section
//
typedef struct tagPineIniParameter {
    char * key;
    char * value;
} PineIniParameter;
//
// * A single section in ini file
//
typedef struct tagPineIniSection {
    char * name;
    int numParam;
    PineIniParameter* params[PINE_INI_MAX_NUM_PARAMETERS];
} PineIniSection;

//
// * The analysis result of ini file
//
typedef struct tagPineIni {
    int numSection;
    PineIniSection* sections[PINE_INI_MAX_NUM_SECTIONS];
} PineIniFile;

//
// * Error Codes
//
#define PINE_INI_ERRCODE_NO                 0
#define PINE_INI_ERRCODE_ILLEGAL_PATTERN    1
#define PINE_INI_ERRCODE_EMPTY_KEY          2
#define PINE_INI_ERRCODE_SECTION_EXCEED     3
#define PINE_INI_ERRCODE_PARAMS_EXCEED      4

extern const char * PINE_INI_ERRMSG[];

typedef struct tagPineIniError {
    int    errorCode;
    int    lineNumber;
    char   lineContent[PINE_INI_LINE_MAX_LEN];
} PineIniError;

//
// Interfaces
//

PineIniParameter*   PineIni_Parameter_New       (const char* key, const char* value);
PineIniParameter*   PineIni_Parameter_Assign    (PineIniParameter* param, const char* value);
void                PineIni_Parameter_Destroy   (PineIniParameter* param);

PineIniSection*     PineIni_Section_New         (const char* sectionName);
PineIniParameter*   PineIni_Section_Find        (const PineIniSection* section, const char* key);
PineIniSection*     PineIni_Section_Append      (PineIniSection* section, const char* key, const char* value);
void                PineIni_Section_Destroy     (PineIniSection* section);

PineIniFile*        PineIni_Parse               (const char * iniText, PineIniError* errorRet);
PineIniSection*     PineIni_Find                (const PineIniFile* file, const char* sectionName);
PineIniFile*        PineIni_Append              (PineIniFile* file, PineIniSection* section);
void                PineIni_Destroy             (PineIniFile* file);

// Utils function

const char*     PineIni_Section_GetString   (const PineIniSection* section, const char* key, const char* defaultValue);
const char*     PineIni_GetString           (const PineIniFile* file, const char* sectionName, const char* key, const char* defaultValue);
int             PineIni_Section_GetInt      (const PineIniSection* section, const char* key, int defaultValue);
int             PineIni_GetInt              (const PineIniFile* file, const char* sectionName, const char* key, int defaultValue);
double          PineIni_Section_GetFloat    (const PineIniSection* section,const char* key,double defaultValue);
double          PineIni_GetFloat            (const PineIniFile* file, const char* sectionName, const char* key, double defaultValue);

// String functions

char*   PineIni_ToSubstring        (char* src, int left, int right);
int     PineIni_FindChar           (const char* src, const char find);
char*   PineIni_Substring          (char* dest, const char* src, int left, int right);
char*   PineIni_StringDump         (const char* src);
char*   PineIni_StringTrim         (char* src);
char*   PineIni_StringRemoveQuotes (char* src);

#define PineIni_StringEquals(str1, str2) (strcmp((str1), (str2)) == 0)

#endif