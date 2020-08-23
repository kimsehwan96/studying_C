#include <stdio.h>

int main () {
    int a, b;
    a = 10;
    b = 3;
    printf("a + b 는 : %d \n", a + b);
    printf("a - b 는 : %d \n", a - b);
    printf("a * b 는 : %d \n", a * b);
    printf("a / b 는 : %d \n", a / b);
    printf("a %% b 는 : %d \n", a % b); // %% 로 한 이유는 %로하면 %d, %f와 같은 포메팅 문자로 인식
    // a % b 는 오직 정수형 데이터들끼리만 연산이 가능함 -> 나머지를 판단하는 연산자
    /*
    a = 10;
    b = 3;
    printf("a / b 는 : %f \n", a / b);
    안된다 왜냐면 %f는 실수형 데이터 출력인데,,,, 10/3 을 해도 정수형 데이터가 저장이 되니까.

    -> 

    int a = 10;
    double b = 3;
    이상태로 위 로직을 도는건 또 된다 
    -> 산술 변환이라는 과정을 거치는데, 자료형이 다른 두 변수를 연산 할 때 숫자의 범위가 큰 자료형으로
    자료형들이 바뀐다.
    */

    return 0;
}