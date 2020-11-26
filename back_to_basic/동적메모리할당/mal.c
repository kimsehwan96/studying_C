#include <stdio.h>
#include <stdlib.h>

int main(void){
    int *a = malloc(sizeof(int)); //int 1개 크기만큼 동적할당
    printf("%p\n", a);
    free(a);
    a = malloc(sizeof(int)); //또 할당
    printf("%p\n", a);      
    free(a);
    return 0;

}