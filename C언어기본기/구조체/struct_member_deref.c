#include <stdio.h>
#include <stdlib.h>

struct Data {
    char c1;
    int *numPtr;
};

int main(void){
    int num1 = 10;
    struct Data d1;
    struct Data *d2 = (struct Data*)malloc(sizeof(struct Data));
    d1.numPtr = &num1;
    d2->numPtr = &num1;
    printf("%d\n", *d1.numPtr);     // 10: 구조체의 멤버를 역참조
    printf("%d\n", *d2->numPtr);    // 10: 구조체 포인터의 멤버를 역참조

    d2->c1 = 'a';
    d1.c1 = 'b';
    printf("%c\n", (*d2).c1);
    printf("%d\n", *(*d2).numPtr);
    printf("%c\n", ((struct Data*)&d1)->c1);
    //(struct Data*)&d1 이렇게하면 구조체 포인터처럼 쓸 수 있나봄
    //그래서 ((struct Data*)&d1)->c1 이렇게 멤버에 접근 가능
    free(d2);
}
