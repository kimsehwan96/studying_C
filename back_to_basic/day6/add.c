// 값에 의한 전달 방식 테스트
#include <stdio.h>

//값에 의한 전달 방식이므로..
void add(int a, int b){
    a = a + b;
    //새롭게 두 변수가 메모리 내에 할당되어서 처리되고
    //a는 새로운 변수라고 생각하면 됨 (메모리가 새로 할당)
}

int main(void){
    int a = 7;
    add(a, 10);
    // 기존 a에는 영향을 주지 못하고, 함수 블럭 내에서만 적용되고
    // 기존 main문의 a라는 변수는 그대로다.
    printf("%d\n", a);
    return 0;
}