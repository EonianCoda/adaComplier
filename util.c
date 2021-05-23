#include "util.h"


void semanticError(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}