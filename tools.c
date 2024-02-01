#include "tools.h"

void strcpyrng(char a[], char b[], int i, int j) {
    int index = 0;
    for (i; i < j; i++) {
        a[index] = b[i];
        index++;
    }
    a[index] = '\0';
}

int nextChar(char string[], char c, int num) {
    int index = 0;
    while (index <= strlen(string) && num > 0) {
        if (string[index] == c) num--;
        index++;
    }
    return index - 1;
}