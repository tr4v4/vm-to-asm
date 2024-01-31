#include <stdio.h>
#include <string.h>

#include "parser.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Inserire file da tradurre (.vm)!\n");
        return 0;
    }

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL) {
        printf("Inserire un file esistente!\n");
        return 0;
    }

    char cString[MAX_COMMAND_LENGTH];
    
    while (advance(fin, cString)) {
        clearString(cString);
        if (!commentOrBlank(cString)) {
            printf("%s\n", cString);
            // TODO
            command cType = commandType(cString);

            char arg1String[MAX_COMMAND_LENGTH];
            arg1(cType, cString, arg1String);
            int arg2Int = arg2(cType, cString);

            printf("%d\t%s\t%d\n", cType, arg1String, arg2Int);
        }
    }

    fclose(fin);

    return 0;
}