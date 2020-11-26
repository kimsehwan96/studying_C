#include <stdio.h>

void process(){
    static int a = 5;
    a = a + 1;
    printf("%d\n", a);
}

int main(){
    process();
    process();
    process();
    process();
    return 0;
}