#include <stdio.h>

enum TYPE {
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT
};

void swapValue(void *ptr1, void *ptr2, enum TYPE t) {
    //반환값 없음, void 포인터 매개변수 두개와
    //변수의 자료형을 알려주기 위한 열겨형을 받음

    switch(t){
        case TYPE_CHAR:
        {
            char temp;
            temp = *(char *)ptr1;
            *(char *)ptr1 = *(char *)ptr2;
            *(char *)ptr2 = temp;
            break;
        }
        case TYPE_INT:
        {
            int temp;
            temp = *(int *)ptr1;
            *(int *)ptr1 = *(int *)ptr2;
            *(int *)ptr2 = temp;
            break;
        }
        case TYPE_FLOAT:
        {
            float temp;
            temp = *(float *)ptr1;
            *(float *)ptr1 = *(float *)ptr2;
            *(float *)ptr2 = temp;
            break;
        }
    }
}

int main(void){
    char c1 = 'a';
    char c2 = 'b';
    swapValue(&c1, &c2, TYPE_CHAR);
    printf("%c %c\n", c1, c2);

    int num1 = 10;
    int num2 = 20;
    swapValue(&num1, &num2,TYPE_INT);
    printf("%d %d\n", num1, num2);

    float num3 = 1.2344f;
    float num4 = 5.3132f;
    swapValue(&num3, &num4, TYPE_FLOAT);
    printf("%f %f\n", num3, num4);

    return 0;
}