#include "parser.h"

char *advance(FILE *fin, char cString[]) {
    return fgets(cString, MAX_COMMAND_LENGTH, fin);
}

void clearString(char string[]) {
    int firstIndex = 0;
    while (firstIndex < strlen(string) &&
           (string[firstIndex] == ' ' || string[firstIndex] == '\t'))
        firstIndex++;
    if (string[strlen(string) - 1] == '\n') {
        if (string[strlen(string) - 2] == '\r')
            strcpyrng(string, string, firstIndex, strlen(string) - 2);
        else
            strcpyrng(string, string, firstIndex, strlen(string) - 1);
    } else
        strcpyrng(string, string, firstIndex, strlen(string));
}

bool commentOrBlank(char string[]) {
    return (strlen(string) <= 1) || (string[0] == '/' && string[1] == '/');
}

command commandType(char cString[]) {
    int firstIndex = 0;
    int lastIndex = nextChar(cString, (char *)" \t", 1);
    char cName[MAX_COMMAND_LENGTH];
    strcpyrng(cName, cString, firstIndex, lastIndex);

    command c;
    if (strncmp(cName, "add", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(cName, "sub", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(cName, "neg", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(cName, "eq", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(cName, "gt", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(cName, "lt", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(cName, "and", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(cName, "or", MAX_COMMAND_LENGTH) == 0 ||
        strncmp(cName, "not", MAX_COMMAND_LENGTH) == 0)
        c = C_ARITHMETIC;
    else if (strncmp(cName, "push", MAX_COMMAND_LENGTH) == 0)
        c = C_PUSH;
    else if (strncmp(cName, "pop", MAX_COMMAND_LENGTH) == 0)
        c = C_POP;
    else if (strncmp(cName, "label", MAX_COMMAND_LENGTH) == 0)
        c = C_LABEL;
    else if (strncmp(cName, "goto", MAX_COMMAND_LENGTH) == 0)
        c = C_GOTO;
    else if (strncmp(cName, "if-goto", MAX_COMMAND_LENGTH) == 0)
        c = C_IF;
    else if (strncmp(cName, "function", MAX_COMMAND_LENGTH) == 0)
        c = C_FUNCTION;
    else if (strncmp(cName, "return", MAX_COMMAND_LENGTH) == 0)
        c = C_RETURN;
    else if (strncmp(cName, "call", MAX_COMMAND_LENGTH) == 0)
        c = C_CALL;
    else
        c = C_INVALID;

    return c;
}

void arg1(command cType, char cString[], char arg[]) {
    switch (cType) {
        case C_ARITHMETIC:
        case C_INVALID: {
            int firstIndex = 0;
            int lastIndex = nextChar(cString, (char *)" \t", 1);
            strcpyrng(arg, cString, firstIndex, lastIndex);
            break;
        }
        case C_PUSH:
        case C_POP:
        case C_LABEL:
        case C_GOTO:
        case C_IF:
        case C_FUNCTION:
        case C_CALL: {
            int firstIndex = nextChar(cString, (char *)" \t", 1);
            int lastIndex = nextChar(cString, (char *)" \t", 2);
            strcpyrng(arg, cString, firstIndex, lastIndex);
            clearString(arg);
            break;
        }
        default: {
            arg[0] = '\0';
            break;
        }
    }
}

int arg2(command cType, char cString[]) {
    switch (cType) {
        case C_PUSH:
        case C_POP:
        case C_FUNCTION:
        case C_CALL: {
            int firstIndex = nextChar(cString, (char *)" \t", 2);
            int lastIndex = nextChar(cString, (char *)" \t", 3);
            char arg[MAX_COMMAND_LENGTH];
            strcpyrng(arg, cString, firstIndex, lastIndex);
            clearString(arg);
            return atoi(arg);
            break;
        }
        default: {
            return -1;
            break;
        }
    }
}