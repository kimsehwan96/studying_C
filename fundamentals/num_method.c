#include <stdio.h>

int main () {
    int a = 127;
    printf("a의 값은 %d 진법으로 %o 입니다. \n", 8, a);
    printf("a의 값은 %d 진법으로 %d 입니다. \n", 10, a);
    printf("a의 값은 %d 진법으로 %x 입니다. \n", 16, a);

    return 0;
}