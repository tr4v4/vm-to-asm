#include <string.h>
#ifndef LOL
#define LOL

const int MAX_COMMAND_LENGTH = 100;
const int MAX_FILENAME_LENGTH = 10;
const int MAX_SEGMENT_LENGTH = 10;
const int MAX_CODE_LENGTH = 500;

typedef enum {
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL,
    C_INVALID
} command;

void strcpyrng(char a[], char b[], int i, int j);
int nextChar(char string[], char c, int num);

#endif