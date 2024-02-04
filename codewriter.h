#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tools.h"

void bootstrap(FILE *fout);
void writeArithmetic(FILE *fout, char cString[]);
void writePushPop(FILE *fout, command cType, char segment[], int index);
void writeFlow(FILE *fout, command cType, char label[]);
void writeFunction(FILE *fout, command cType, char function[], int vars);