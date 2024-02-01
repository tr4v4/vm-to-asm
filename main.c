#include <stdio.h>
#include <string.h>

#include "codewriter.h"
#include "parser.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Inserire file da tradurre (.vm)!\n");
        return 0;
    }

    // Apri file .vm
    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL) {
        printf("Inserire un file esistente!\n");
        return 0;
    }

    // Crea file .asm
    char fName[MAX_FILENAME_LENGTH];
    int firstIndex = 0;
    int lastIndex = nextChar(argv[1], '.', 1);
    strcpyrng(fName, argv[1], firstIndex, lastIndex);
    strncat(fName, ".asm", 4);
    FILE *fout = fopen(fName, "w");

    bootstrap(fout);

    char cString[MAX_COMMAND_LENGTH];
    while (advance(fin, cString)) {
        clearString(cString);
        if (!commentOrBlank(cString)) {
            printf("%s\n", cString);
            command cType = commandType(cString);
            if (cType == C_ARITHMETIC) {
                writeArithmetic(fout, cString);
            } else if (cType == C_PUSH || cType == C_POP) {
                char arg1String[MAX_COMMAND_LENGTH];
                arg1(cType, cString, arg1String);
                int arg2Int = arg2(cType, cString);
                printf("%d\t%s\t%d\n", cType, arg1String, arg2Int);
                writePushPop(fout, cType, arg1String, arg2Int);
            }
        }
    }

    fclose(fout);
    fclose(fin);

    return 0;
}