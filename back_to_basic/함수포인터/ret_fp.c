#include <stdio.h>

int add(int a, int b){
    return a + b;
}

int(*process(char* a))(int, int){
    printf("result : %s \n", a);
    return add;
}

int main (void){
    printf("%d\n", process("10과 20을 더해보겠다")(10, 20));
    return 0;
}