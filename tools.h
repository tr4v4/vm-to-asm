#include <string.h>

const int MAX_COMMAND_LENGTH = 30;
const int MAX_FILENAME_LENGTH = 10;

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