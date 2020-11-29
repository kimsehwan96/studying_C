#include <stdio.h>

int main(void){
    int a[5] = { 1, 2, 3, 4, 5};
    int *b = a;
    // 정수형 포인터 변수 b를 선언했다.
    // a는 배열의 첫번째값이 담긴 '주소'를 의미한다.
    // 위처럼 사용하면 b[5]라는 배열을 쓰는것과 동일
    printf("%d\n", b[2]);
    return 0;
}