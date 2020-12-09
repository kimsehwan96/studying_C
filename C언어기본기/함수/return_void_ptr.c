#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *allocMemory(void){
    void *ptr = malloc(100);
    
    return ptr; //void 포인터 반환
}

int main(void){
    char *s1 = allocMemory(); //void 포인터를 char포인터에 넣어 문자열처럼 사용
    strcpy(s1, "Hello World !");
    printf("%s \n", s1);
    free(s1);

    int *numPtr1 = allocMemory();//void 포인터를 int 포인터에 넣어서 정수 배열처러 사용
    numPtr1[0] = 10; //첫번째 요소에 10 저장
    numPtr1[1] = 20; //두번째 요소애 20저장

    printf("%d %d \n", numPtr1[0], numPtr1[1]); //10, 20
    free(numPtr1);

    return 0;
}