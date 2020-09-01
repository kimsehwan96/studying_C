#include <stdio.h>

int main() {
    
    int num1 = 0;
    int size;

    size = sizeof num1;

    printf("size of num1 : %d\n", size);

    return 0;

    // size of num1 : 4  -> 4bytes.
}