#include "codewriter.h"

void bootstrap(FILE *fout) {
    // SP (RAM[0]) = 256
    char code[MAX_COMMAND_LENGTH] = "@256\nD=A\n@0\nM=D\n";
    fputs(code, fout);
}