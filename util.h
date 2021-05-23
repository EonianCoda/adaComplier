#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define DEBUG_FLAG (true)


enum TypeEnum {
    Type_INT, Type_REAL, Type_BOOL, Type_STR, Type_ARRAY, Type_VOID
};


struct Constant{
  enum TypeEnum type;
  union {
    char *str;
    int integer;
    float real;
    bool boolean;
  };
};

struct Type{
  enum TypeEnum type;
  // For Array Type
  int size;
  enum TypeEnum itemType;
};

void semanticError(const char *msg);