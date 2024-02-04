#include "tools.h"

void strcpyrng(char a[], char b[], int i, int j) {
    int index = 0;
    for (i; i < j; i++) {
        a[index] = b[i];
        index++;
    }
    a[index] = '\0';
}

int nextChar(char string[], char c[], int num) {
    int index = 0;
    bool inside = false;
    while (index <= strlen(string) && num > 0) {
        bool found = false;
        for (int i = 0; i < strlen(c) && !found; i++) {
            if (string[index] == c[i]) {
                found = true;
            }
        }

        if (found) {
            if (!inside) {
                num--;
                inside = true;
            }
        } else {
            inside = false;
        }

        index++;
    }
    return index - 1;
}