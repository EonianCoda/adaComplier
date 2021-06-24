#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define StringCapacity (60)


struct String{
    char *buf;
    int capacity;
    int size;
};


void initString(struct String *str);
void appendString(struct String *str, const char *text);
void destroyString(struct String *str);
void clearString(struct String *str);
