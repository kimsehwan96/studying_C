#include <stdio.h>

int main() {

    char num1 = 128; // char는 정수 자료형이다!!!! -128 ~ 127까지. -> 오버플로우 나겠지
    unsigned char num2 = 255;

    printf(" %d %d \n", num1, num2);

    return 0; 

    // char -> 1바이트, short -> 2바이트, int -> 4바이트, long -> 4바이트 long long -> 8바이트
    // long은 운영체제랑 플랫폼마다 다르당 크기가
}