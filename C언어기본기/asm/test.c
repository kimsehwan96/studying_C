#include <stdio.h>

void dice(int input){
    printf("throw dice! %d\n", input);
}

int add(int a, int b){
    return a + b;
}

int main(void) {
    int x = 10;
    int y = 20;
    printf("%d\n", add(x,y));
    return 0;
}

//test.asm은 xcode에서 이 소스코드를 어셈블리로 변환해준 것.