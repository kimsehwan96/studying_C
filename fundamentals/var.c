#include <stdio.h>


// 자료형 
// 정수형은 short int long이 있다. 이건 버퍼의 크기에 따라 나뉜다
// short는 2바이트 , int는 4바이트, long은 8바이트
// 실수형 자료에는 float, double, long double이 있다.
// 문자형은 char가 있다.
// char는 1바이트. ascii 이용..


// 변수와 상수. 상수는 한번 결정되면 변하지 않고 사용되는 값이다.
// 리터럴 상수와 심벌릭 상수로 구분된다.
// 리터럴 상수는 사용자가 입력한 그대로를 나타내는 것이라고 함.

// 심볼릭 상수는 변수처럼 상수에 이름을 붙여서 프로그램 여러곳에서 사용
// const 라는 예약어를 사용하여 선언하거나 
// #define 문을 이용해 사용 #define 매크로이름 값 
// 매직 넘버는 .h 헤더파일에 #define 으로 미리 정의하고 사용하는 편
// 상수는 대문자로 표현하는 편

int main ()
{
    int b = 0;
    int a = 0;
    //int sum = 0;
    const double PI = 3.141592;
    int radius = 5;


    a = 5;
    b = 10;
    printf("this is num a : %d \n", a);
    printf("this is num b : %d \n", b);
    int sum = a+b;
    printf("sum of a & b is %d \n", sum);

    printf("원의 반지름은 %d , 원의 넓이는 %f \n", radius, PI * radius * radius) ;


}