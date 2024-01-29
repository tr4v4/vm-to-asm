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

    char commandString[MAX_COMMAND_LENGTH];
    
    while (advance(fin, commandString)) {
        clearString(commandString);
        if (!commentOrBlank(commandString)) {
            printf("%s\n", commandString);
            // TODO
            command c = commandType(commandString);
            printf("%d\n", c);
        }
    }

    fclose(fin);

    return 0;
}