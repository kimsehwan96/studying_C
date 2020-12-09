#include <stdio.h>
#include <stdlib.h>

void allocMemory(void *ptr, int size) {
    ptr = malloc(size); //ptr는 alloc Memory를 넘어가면 사용 불가능함
}

int main(void) {
    long long *numPtr = NULL;

    allocMemory(numPtr, sizeof(long long));
    *numPtr = 10;
    printf("%lld \n", *numPtr);
    free(numPtr);
    return 0;
}

//세그폴트 뜸