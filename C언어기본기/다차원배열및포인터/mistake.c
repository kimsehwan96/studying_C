#include <stdio.h>

int main(void){
    int a = 10;
    int b[10];
    b = &a;
    //b 즉 배열 이름은 상수이기 때문에 변경 할 수 없다.
    return 0;
}