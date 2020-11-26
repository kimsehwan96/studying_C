#include <stdio.h>

void add (int* a){
    *a = (*a) + 10;
}

void mul (int* a){
    *a = (*a)*10;
}

int main(void){
    int a = 5;
    void (*fp)(int *) = add;
    fp(&a);
    printf("%d\n", a);
    fp = mul;
    fp(&a);
    printf("%d\n", a);

    return 0;
    
}