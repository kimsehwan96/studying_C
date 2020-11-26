#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    char *a = malloc(100); //100bytes, 1개 char 100개
    memset(a, 'A', 100);
    for (int i = 0; i <100; i++){
        printf("%c\n", a[i]);
    }
    return 0;
}