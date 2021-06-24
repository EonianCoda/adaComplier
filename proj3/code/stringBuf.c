#include "stringBuf.h"


void initString(struct String *str)
{
    str->buf =  malloc(sizeof(char) * (StringCapacity + 1));
    str->capacity = StringCapacity + 1;
    str->size = 0;
}

void appendString(struct String *str, const char *text)
{
    int length = strlen(text);
    if(length == 0) return;
    int newSize = str->size + length;
    if(newSize > str->capacity)
    {
        char *n = realloc(str->buf, newSize + 1);
        if (n == NULL) { exit(-1); } // failed
        str->buf = n;
        str->capacity = newSize + 1;
    }

    strncpy(str->buf + str->size, text, length);
    str->size += length;
    *(str->buf + str->size) = '\0';
}
void destroyString(struct String *str)
{
    if(str->buf != NULL) free(str->buf);
    str->capacity = 0;
}
void clearString(struct String *str)
{
    str->buf[0] = '\0';
    str->size = 0;
}
