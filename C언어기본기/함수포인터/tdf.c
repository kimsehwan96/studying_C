#include <stdio.h>

typedef void (*FuncPtr)(int*);

void add (int* a){
    *a = (*a) + 10;
}

void mul (int* a){
    *a = (*a)*10;
}

int main(void){
    FuncPtr fp;
    int a = 5;
    fp = add;
    fp(&a);
    printf("%d\n", a);
    fp = mul;
    fp(&a);
    printf("%d\n", a);

    return 0;
    
}