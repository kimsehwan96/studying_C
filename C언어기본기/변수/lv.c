#include <stdio.h>

int main () {
    int a = 5;
    if (1) {
        int a = 7;
    }
    printf("%d\n", a);
    return 0;
}