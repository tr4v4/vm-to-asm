#include <stdio.h>
#include <stdlib.h>

#include "tools.h"

char *advance(FILE *fin, char cString[]);
void clearString(char string[]);
bool commentOrBlank(char string[]);
command commandType(char cString[]);
void arg1(command cType, char cString[], char arg[]);
int arg2(command cType, char cString[]);