#include <stdio.h>

int a = 5;

void changeVal() {
    a = 10;
}


int main () {
    printf("%d\n", a);
    changeVal();
    printf("%d\n", a);
    return 0;
}