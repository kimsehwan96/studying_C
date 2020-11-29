// 매개변수 및 반환 자료형이 없는 함수 포인터.

// 함수는 메모리 주소를 가질 수 있다.
// 그래서 함수으 메모리 주소를 가질 수 있는 '함수포인터' 도 존재하는 것
// function() <- 함수를 호출하는거
// function <- 해당 함수 메모리 주소!
#include <stdio.h>

void myFunction(){
    printf("this is my function \n");
}

void yourFunction(){
    printf("this is your function \n");
}

int main(void){
    void(*fp)() = myFunction;
    // void     (*fp)      ()
    // 반환자료형  포인터이름  매개변수가 없음
    fp();
    fp = yourFunction;
    fp();
    return 0;
}