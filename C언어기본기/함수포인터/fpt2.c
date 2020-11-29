#include <stdio.h>

int add(int a, int b){
    return a + b;
}

int mul(int a, int b){
    return a * b;
}

int main(void){
    int (*fp)(int, int);
    //반환 자료형 | 포인터 이름 | 매개변수들
    fp = add;
    printf("%d\n", fp(10, 20));
    fp = mul;
    printf("%d\n", fp(10, 20));

    return 0;
}