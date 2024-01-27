const int MAX_COMMAND_LENGTH = 30;

enum command {
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
};

void strcpyrng(char a[], char b[], int i, int j);