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
    strncat(fName, ".asm", 5);
    FILE *fout = fopen(fName, "w");

    bootstrap(fout);

    char cString[MAX_COMMAND_LENGTH];
    while (advance(fin, cString)) {
        clearString(cString);
        if (!commentOrBlank(cString)) {
            printf("%s\n", cString);

            command cType = commandType(cString);
            char a1[MAX_COMMAND_LENGTH];
            int a2;

            arg1(cType, cString, a1);
            a2 = arg2(cType, cString);

            if (cType == C_ARITHMETIC) {
                writeArithmetic(fout, cString);
            } else if (cType == C_PUSH || cType == C_POP) {
                printf("%d\t%s\t%d\n", cType, a1, a2);
                writePushPop(fout, cType, a1, a2);
            } else if (cType == C_LABEL || cType == C_GOTO || cType == C_IF) {
                printf("%d\t%s\n", cType, a1);
                writeFlow(fout, cType, a1);
            } else if (cType == C_FUNCTION || cType == C_CALL ||
                       cType == C_RETURN) {
                printf("%d\t%s\t%d\n", cType, a1, a2);
                writeFunction(fout, cType, a1, a2);
            }
        }
    }

    fclose(fout);
    fclose(fin);

    return 0;
}