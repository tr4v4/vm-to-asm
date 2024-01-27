#include "parser.h"

char *advance(FILE *fin, char commandString[]) {
    return fgets(commandString, 30, fin);
}

command commandType(char commandString[]) {
    // Parto dalla prima lettera dell'alfabeto
    int firstIndex = 0;
    while (commandString[firstIndex] < 'a' || commandString[firstIndex] > 'z')
        firstIndex++;

    // Arrivo fino allo spazio o "fine riga" successivo
    int lastIndex = firstIndex + 1;
    while (commandString[lastIndex] != ' ' && commandString[lastIndex] != '\n')
        lastIndex++;

    char commandName[MAX_COMMAND_LENGTH];
    strcpyrng(commandName, commandString, firstIndex, lastIndex);

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