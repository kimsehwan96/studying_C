// 2차원 배열을 포인터 및 동적 할당을 이용해 구현


#include <stdio.h>
#include <stdlib.h>

int main(void){
    int** p = (int**)malloc(sizeof(int*) * 3);
        for (int i = 0; i < 3; i++){
            *(p + i) = (int*)malloc(sizeof(int)*3);
        }
        for (int i = 0; i < 3 ; i++){
            for (int j = 0 ; j < 3 ; j++) {
                *(*(p+i) + j) = i * 3 + j;
            }
        }
        for (int i = 0; i < 3 ; i++){
            for (int j = 0 ; j < 3 ; j++) {
                printf("%d", *(*(p+i) + j));
            }
            printf("\n");
        }

        return 0;
}