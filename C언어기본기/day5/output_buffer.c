#include <stdio.h>
#include <time.h>

void delay(unsigned int sec) {
    clock_t ticks1 = clock();
    clock_t ticks2 = ticks1;
    while((ticks2 / CLOCKS_PER_SEC - ticks1 / CLOCKS_PER_SEC) < (clock_t)sec)
        ticks2 = clock();
}

int main(void) {
    setvbuf(stdout, NULL, _IOFBF, 10); // 출력 버퍼 크기를 10으로 설정
    
    printf("Hello, wolrd\n");
    delay(3); //3초간 기다림
    
    return 0;
}
