#include <stdlib.h>
#include "pine-ini.h"

#define isWhitespace(c) ((c) == ' ' || c == '\r' || c == '\n' || c == '\t')

const char *PINE_INI_ERRMSG[] = {
    "No error",
    "Illegal pattern",
    "Empty key",
    "Sections exceed",
    "Parameters exceed"};

//
// * Parser
//

#define PARSER_ACTION_CONTINUE 1
#define PARSER_ACTION_END 0

typedef struct tagPineIniParser
{
    const char *textBuffer;
    const char *currentPointer;
    int lineNumber;
} PineIniParser;

static PineIniParser *PineIni_Parser_New(const char *textBuffer)
{
    PineIniParser *parser = (PineIniParser *)malloc(sizeof(PineIniParser));

    parser->textBuffer = textBuffer;
    parser->currentPointer = parser->textBuffer;
    parser->lineNumber = 0;

    return parser;
}

static void PineIni_Parser_Destroy(PineIniParser *parser)
{
    if (parser)
    {
        free(parser);
    }
}

//
// Return
// PARSER_ACTION_END        -> buffer end
// PARSER_ACTION_CONTINUE   -> buffer has follow-up content
//
static int PineIni_Parser_Gets(PineIniParser *parser, char *buf)
{
    char *pBuf = buf;

    parser->lineNumber++;

    while (*parser->currentPointer != '\n' && *parser->currentPointer != '\0')
    {
        *(pBuf++) = *(parser->currentPointer++);
    }

    *pBuf = '\0';

    if (*parser->currentPointer == '\0')
    {
        return PARSER_ACTION_END;
    }
    else
    {
        // Skip LF
        parser->currentPointer++;
        return PARSER_ACTION_CONTINUE;
    }
}

static PINE_BOOL PineIni_Line_Empty(const char *line, const int length)
{
    if (length <= 0 || PineIni_StringEquals("", line))
    {
        return PINE_TRUE;
    }
    return PINE_FALSE;
}

static PINE_BOOL PineIni_Line_IsComment(const char *line, const int length)
{
    if (length >= 1 && line[0] == ';')
    {
        return PINE_TRUE;
    }
    return PINE_FALSE;
}

static PINE_BOOL PineIni_Line_IsSection(const char *line, const int length)
{
    if (length >= 2 && line[0] == '[' && line[length - 1] == ']')
    {
        return PINE_TRUE;
    }
    return PINE_FALSE;
}

static PINE_BOOL PineIni_Line_IsParameter(const char *line, const int length)
{
    int i;
    for (i = 0; i < length; ++i)
    {
        if (line[i] == '=')
        {
            return PINE_TRUE;
        }
    }
    return PINE_FALSE;
}

//
// * Parse API
//

#define PARSER_RETURN_ERROR(error_code)        \
    (void *)0;                                 \
    errorRet->lineNumber = parser->lineNumber; \
    errorRet->errorCode = (error_code);        \
    strcpy(errorRet->lineContent, lineBuffer); \
    PineIni_Parser_Destroy(parser);            \
    PineIni_Destroy(iniResult);                \
    return NULL;

PineIniFile *PineIni_Parse(const char *iniText, PineIniError *errorRet)
{
    char lineBuffer[PINE_INI_LINE_MAX_LEN];
    int lineLength;
    int getsRetCode;
    PineIniParser *parser;
    PineIniFile *iniResult;
    PineIniSection *currentSection;

    parser = PineIni_Parser_New(iniText);

    // Create iniResult
    iniResult = (PineIniFile *)malloc(sizeof(PineIniFile));
    iniResult->numSection = 0;

    // Create a default section for file
    // and append to iniResult
    currentSection = PineIni_Section_New("_default");
    PineIni_Append(iniResult, currentSection);

    // Clear error info
    errorRet->lineNumber = 0;
    errorRet->errorCode = PINE_INI_ERRCODE_NO;
    strcpy(errorRet->lineContent, "");

    do
    {
        // Get line from parser
        getsRetCode = PineIni_Parser_Gets(parser, lineBuffer);

        // Trim white spaces
        PineIni_StringTrim(lineBuffer);

        // Check pattern
        lineLength = strlen(lineBuffer);

        // Pattern : empty
        if (PineIni_Line_Empty(lineBuffer, lineLength))
        {
            continue;
        }
        // Pattern : comment
        else if (PineIni_Line_IsComment(lineBuffer, lineLength))
        {
            continue;
        }
        // Pattern : section
        else if (PineIni_Line_IsSection(lineBuffer, lineLength))
        {
            char sectionName[PINE_INI_LINE_MAX_LEN];
            PineIniSection *section;

            PineIni_Substring(sectionName, lineBuffer, 1, lineLength - 2);

            section = PineIni_Find(iniResult, sectionName);

            // Section name not exist in iniResult
            if (section == NULL)
            {
                // Check if exceed
                if (iniResult->numSection >= PINE_INI_MAX_NUM_SECTIONS)
                {
                    PARSER_RETURN_ERROR(PINE_INI_ERRCODE_SECTION_EXCEED);
                }

                // Create a new section and append in iniResult
                section = PineIni_Section_New(sectionName);
                PineIni_Append(iniResult, section);
            }

            currentSection = section;

            continue;
        }
        // Pattern : parameter
        else if (PineIni_Line_IsParameter(lineBuffer, lineLength))
        {
            char key[PINE_INI_LINE_MAX_LEN];
            char value[PINE_INI_LINE_MAX_LEN];
            int equalPos;
            PineIniParameter *param;

            // Get key and value
            equalPos = PineIni_FindChar(lineBuffer, '=');
            PineIni_Substring(key, lineBuffer, 0, equalPos - 1);
            PineIni_Substring(value, lineBuffer, equalPos + 1, lineLength - 1);
            PineIni_StringTrim(key);
            PineIni_StringRemoveQuotes(value);

            // Error: empty key
            if (strlen(key) <= 0)
            {
                PARSER_RETURN_ERROR(PINE_INI_ERRCODE_EMPTY_KEY);
            }

            // Check if key already exist
            param = PineIni_Section_Find(currentSection, key);

            // Exist, update value
            if (param)
            {
                PineIni_Parameter_Assign(param, value);
            }
            // Not exist, append to current section
            else
            {
                // Check if exceed
                if (currentSection->numParam >= PINE_INI_MAX_NUM_PARAMETERS)
                {
                    PARSER_RETURN_ERROR(PINE_INI_ERRCODE_PARAMS_EXCEED);
                }
                PineIni_Section_Append(currentSection, key, value);
            }

            continue;
        }
        // Illegal Pattern!
        else
        {
            PARSER_RETURN_ERROR(PINE_INI_ERRCODE_ILLEGAL_PATTERN);
        }

    } while (getsRetCode != PARSER_ACTION_END);

    PineIni_Parser_Destroy(parser);

    return iniResult;
}

PineIniSection *PineIni_Find(const PineIniFile *file, const char *sectionName)
{
    if (file)
    {
        int i;
        for (i = 0; i < file->numSection; ++i)
        {
            PineIniSection *section = file->sections[i];
            if (PineIni_StringEquals(sectionName, section->name))
            {
                return section;
            }
        }
    }
    return NULL;
}

PineIniFile *PineIni_Append(PineIniFile *file, PineIniSection *section)
{
    if (file)
    {
        file->sections[file->numSection++] = section;
    }
    return file;
}

void PineIni_Destroy(PineIniFile *file)
{
    if (file)
    {
        int i;

        // destroy sections in file
        for (i = 0; i < file->numSection; ++i)
        {
            PineIni_Section_Destroy(file->sections[i]);
        }

        // free file self
        free(file);
    }
}

// Section

PineIniSection *PineIni_Section_New(const char *sectionName)
{
    PineIniSection *section = (PineIniSection *)malloc(sizeof(PineIniSection));

    section->name = PineIni_StringDump(sectionName);
    section->numParam = 0;

    return section;
}

PineIniParameter *PineIni_Section_Find(const PineIniSection *section, const char *key)
{
    if (section)
    {
        int i;
        for (i = 0; i < section->numParam; ++i)
        {
            PineIniParameter *param = section->params[i];
            if (PineIni_StringEquals(key, param->key))
            {
                return param;
            }
        }
    }
    return NULL;
}

PineIniSection *PineIni_Section_Append(PineIniSection *section, const char *key, const char *value)
{
    if (section)
    {
        section->params[section->numParam++] = PineIni_Parameter_New(key, value);
    }
    return section;
}

void PineIni_Section_Destroy(PineIniSection *section)
{
    if (section)
    {
        int i;

        // free section name
        if (section->name)
        {
            free(section->name);
        }
        // destroy parameters in section
        for (i = 0; i < section->numParam; ++i)
        {
            PineIni_Parameter_Destroy(section->params[i]);
        }
        // free section self
        free(section);
    }
}

// Parameter

PineIniParameter *PineIni_Parameter_New(const char *key, const char *value)
{
    PineIniParameter *param;

    param = (PineIniParameter *)malloc(sizeof(PineIniParameter));
    param->key = PineIni_StringDump(key);
    param->value = PineIni_StringDump(value);

    return param;
}

PineIniParameter *PineIni_Parameter_Assign(PineIniParameter *param, const char *value)
{
    if (param)
    {
        if (param->value)
        {
            free(param->value);
        }
        param->value = PineIni_StringDump(value);
    }
    return param;
}

void PineIni_Parameter_Destroy(PineIniParameter *param)
{
    if (param)
    {
        if (param->key)
        {
            free(param->key);
        }
        if (param->value)
        {
            free(param->value);
        }
        free(param);
    }
}

// Utils functions

const char *PineIni_Section_GetString(const PineIniSection *section, const char *key, const char *defaultValue)
{
    const PineIniParameter *param = PineIni_Section_Find(section, key);

    // key not found or value is null
    if (!param || !param->value)
    {
        return defaultValue;
    }

    return param->value;
}

const char *PineIni_GetString(const PineIniFile *file, const char *sectionName, const char *key, const char *defaultValue)
{
    const PineIniSection *section = PineIni_Find(file, sectionName);

    // sectionName not found
    if (!section)
    {
        return defaultValue;
    }

    return PineIni_Section_GetString(section, key, defaultValue);
}

int PineIni_Section_GetInt(const PineIniSection *section, const char *key, int defaultValue)
{
    const char *szIntVal = PineIni_Section_GetString(section, key, NULL);

    if (szIntVal == NULL)
    {
        return defaultValue;
    }
    else
    {
        return atol(szIntVal);
    }
}

int PineIni_GetInt(const PineIniFile *file, const char *sectionName, const char *key, int defaultValue)
{
    const char *szIntVal = PineIni_GetString(file, sectionName, key, NULL);

    if (szIntVal == NULL)
    {
        return defaultValue;
    }
    else
    {
        return atol(szIntVal);
    }
}

double PineIni_Section_GetFloat(const PineIniSection *section, const char *key, double defaultValue)
{
    const char *szIntVal = PineIni_Section_GetString(section, key, NULL);
    if (szIntVal == NULL)
    {
        return defaultValue;
    }
    else
    {
        return atof(szIntVal);
    }
}
double PineIni_GetFloat(const PineIniFile *file, const char *sectionName, const char *key, double defaultValue)
{
    const char *szIntVal = PineIni_GetString(file, sectionName, key, NULL);

    if (szIntVal == NULL)
    {
        return defaultValue;
    }
    else
    {
        return atof(szIntVal);
    }
}

// String functions

int PineIni_FindChar(const char *src, const char find)
{
    int i;
    for (i = 0; src[i]; ++i)
    {
        if (src[i] == find)
        {
            return i;
        }
    }
    return -1;
}

char *PineIni_Substring(char *dest, const char *src, int left, int right)
{
    char *buf = dest;
    int newLength = 0;
    int i;

    for (i = left; i <= right; ++i)
    {
        buf[newLength++] = src[i];
    }

    buf[newLength] = 0;

    return dest;
}

char *PineIni_ToSubstring(char *src, int left, int right)
{
    int length = strlen(src);
    char *buf = (char *)malloc(length + 1);
    int newLength = 0;
    int i;

    for (i = left; i <= right; ++i)
    {
        buf[newLength++] = src[i];
    }

    buf[newLength] = 0;

    strcpy(src, buf);

    free(buf);

    return src;
}

char *PineIni_StringDump(const char *src)
{
    int length = strlen(src);
    char *dup = (char *)malloc(length + 1);
    strcpy(dup, src);
    return dup;
}

char *PineIni_StringTrim(char *src)
{
    int length = strlen(src);
    int left;
    int right;
    int newLength = 0;

    for (left = 0; left < length; ++left)
    {
        if (!isWhitespace(src[left]))
        {
            break;
        }
    }

    for (right = length - 1; right >= 0; --right)
    {
        if (!isWhitespace(src[right]))
        {
            break;
        }
    }

    return PineIni_ToSubstring(src, left, right);
}

char *PineIni_StringRemoveQuotes(char *src)
{
    int length;
    int isSingleQuotesAround;
    int isDoubleQuotesAround;

    PineIni_StringTrim(src);

    // Too short, no need to check
    if ((length = strlen(src)) < 2)
    {
        return src;
    }

    isSingleQuotesAround = (src[0] == '"' && src[length - 1] == '"');
    isDoubleQuotesAround = (src[0] == '\'' && src[length - 1] == '\'');

    if (!isSingleQuotesAround && !isDoubleQuotesAround)
    {
        return src;
    }

    return PineIni_ToSubstring(src, 1, length - 2);
}