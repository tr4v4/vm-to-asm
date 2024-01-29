#include <stdio.h>
#include <string.h>

#include "tools.h"

char *advance(FILE *fin, char command[]);
void clearString(char string[]);
bool commentOrBlank(char string[]);
command commandType(char command[]);
void arg1(char command[], char arg[]);
int arg2(char command[]);