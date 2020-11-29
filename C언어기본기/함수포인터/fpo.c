#include <stdio.h>

void function(){
    printf("It's my function");
}

int main (void){
    printf("%p\n", function);
    return 0;
}