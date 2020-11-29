#include <stdio.h>
#include <stdlib.h>

int main(){
    char a[100];
    gets_s(a, sizeof(a));
    printf("%s\n", a);
    return 0;
}