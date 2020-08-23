#include<stdio.h>

int main()
{
    int i;
    int *pi; //포인터 변수 선언

    i = 10;
    pi = &i; //포인터 변수 pi에 i의 주소를 저장, &변수 -> 변수의 주소지

    printf("first addres of i %x\n", &i);
    printf("value of i: %d\n", i);
    printf("address of i %x\n", pi);


    *pi = 100;
    printf("value of real pi %d\n", *pi);
    printf("value of chaged i %d\n", i);
    printf("addres of pi %x\n",pi);
    printf("address of poniter var %x\n",&pi);
}