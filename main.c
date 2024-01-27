#include <stdio.h>
#include <string.h>

#include "parser.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Inserire file da tradurre (.vm)!\n");
        return 0;
    }

    FILE *fin = fopen(argv[1], "r");
    char commandString[MAX_COMMAND_LENGTH];

    while (advance(fin, commandString)) {
        printf("%s", commandString);
        // TODO
        commandType(commandString);
    }

    fclose(fin);

    return 0;
}