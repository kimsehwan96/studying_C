#include <stdio.h>

int main(void){
    int a[5] = { 1, 2, 3, 4, 5};
    int *p = a;
    printf("%d\n", *(p++)); 
    //1 -> 참조 후 포인터의 주소값 증가 (즉 &a[0], a 의 주소에 값을 참조 후 주소값 증가)
    printf("%d\n", *(++p)); 
    //3 -> &a[1]을 가르키는 포인터의 상태에서, ++로 먼저 포인터 주소값 증가 시킨 후 값을 참조 즉 a[2] 참조
    printf("%d\n", *(p+2)); 
    //5  -> &a[2]를 가르키는 포인터 주소값에서 2증가시켰으니 &a[5] 주소에 들어있는 값 참조
    p = a;
    printf("%d\n", *(++p));
}