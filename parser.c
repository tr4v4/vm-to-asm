#include "parser.h"

char *advance(FILE *fin, char commandString[]) {
    return fgets(commandString, 30, fin);
}

void clearString(char string[]) {
    int firstIndex = 0;
    while (firstIndex < strlen(string) && (string[firstIndex] == ' ' || string[firstIndex] == '\t'))
        firstIndex++;
    strcpyrng(string, string, firstIndex, strlen(string));
    string[strlen(string)-1] = '\0';
}

bool commentOrBlank(char string[]) {
    return (strlen(string) <= 1) || (string[0] == '/' && string[1] == '/');
}

command commandType(char commandString[]) {
    // Arrivo fino allo spazio o "fine riga" successivo
    int lastIndex = 0;
    while (lastIndex < strlen(commandString) && commandString[lastIndex] != ' ' && commandString[lastIndex] != '\n')
        lastIndex++;

    char commandName[MAX_COMMAND_LENGTH];
    strcpyrng(commandName, commandString, 0, lastIndex);

    command c;
    if (strncmp(commandName, "add", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(commandName, "sub", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(commandName, "neg", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(commandName, "eq", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(commandName, "gt", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(commandName, "lt", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(commandName, "and", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(commandName, "or", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(commandName, "not", MAX_COMMAND_LENGTH) == 0)
        c = C_ARITHMETIC;
    else if (strncmp(commandName, "push", MAX_COMMAND_LENGTH) == 0)
        c = C_PUSH;
    else if (strncmp(commandName, "pop", MAX_COMMAND_LENGTH) == 0)
        c = C_POP;
    else if (strncmp(commandName, "label", MAX_COMMAND_LENGTH) == 0)
        c = C_LABEL;
    else if (strncmp(commandName, "goto", MAX_COMMAND_LENGTH) == 0)
        c = C_GOTO;
    else if (strncmp(commandName, "if-goto", MAX_COMMAND_LENGTH) == 0)
        c = C_IF;
    else if (strncmp(commandName, "function", MAX_COMMAND_LENGTH) == 0)
        c = C_FUNCTION;
    else if (strncmp(commandName, "return", MAX_COMMAND_LENGTH) == 0)
        c = C_RETURN;
    else if (strncmp(commandName, "call", MAX_COMMAND_LENGTH) == 0)
        c = C_CALL;
    else
        c = C_INVALID;

    return c;
}


void arg1(char command[], char arg[]) {
    switch (commandType(command)) {
        case C_ARITHMETIC: {
            int lastIndex = 0;
            while (command[lastIndex] != ' ' && command[lastIndex] != '\n')
                lastIndex++;
            strcpyrng(arg, command, 0, lastIndex);
            break;
        }
        case C_PUSH: {
            // Arrivo al primo spazio
            int lastIndex = 0;
            while (command[lastIndex] != ' ' && command[lastIndex] != '\n')
                lastIndex++;
            // Scorro fino al successivo spazio o "fine-riga"
            break;
        }
    }
}
