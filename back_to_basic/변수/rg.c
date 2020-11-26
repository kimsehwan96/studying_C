#include <stdio.h>

int main(void){
    register int a = 10, i;
    for (i=0; i < a; i++){
        printf("%d\n", a);
    }
    return 0;
}