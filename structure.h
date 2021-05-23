#pragma once
#include <stdbool.h>

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

struct Type {
  enum TypeEnum type;
  // only for array
  int upperBound;
  struct Type *itemType;
};