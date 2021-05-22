#pragma once


enum TypeEnum {
    Type_INT, Type_REAL, Type_BOOL, Type_STRING, Type_ARRAY, Type_VOID
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