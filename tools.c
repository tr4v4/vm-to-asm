#include "tools.h"

void strcpyrng(char a[], char b[], int i, int j) {
    int index = 0;
    for (i; i < j; i++) {
        a[index] = b[i];
        index++;
    }
    a[index] = '\0';
}