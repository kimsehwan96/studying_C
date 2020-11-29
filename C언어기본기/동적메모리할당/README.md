# 동적 메모리 할당
- 일반적으로 C언어에서의 배열의 경우 사전에 적절한 크기만큼 할당해주어야 한다.
- 우리가 원하는 만큼만 메모리를 할당해서 사용하고자 한다면 동적 메모리 할당을 사용한다.
- 동적이라는 말의 의미는 프로그램 실행 도중을 의미함.


## 동적 메모리 할당 함수

1. C언어에서는 malloc() 함수를 이용해 원하는 만큼의 메모리 공간 확보 가능
2. malloc()함수는 메모리 할당에 성공하면 주소를 반환하고, 실패시 NULL을 반환함
3. malloc()함수는 stdlib.h 라이브리에 정의되어 있음.

`malloc(할당할 바이트 크기)`
 
 ```c
 #include <stdio.h>
#include <stdlib.h>

int main(void){
    int *a = malloc(sizeof(int)); //int 1개 크기만큼 동적할당
    printf("%p\n", a);
    a = malloc(sizeof(int)); //또 할당
    printf("%p\n", a);      
    return 0;

}
```

- 동적 할당된 변수는 힙 영역에 할당됨.

1. 전통적인 C에서는 스택에 선언된 변수는 메모리 해제 안해도 됨
2. 동적 할당 변수는 반드시 free() 함수로 메모리 해제를 해줘야 함
3. 매모리 해제를 하지 않으면 메모리 누수가 발생함.

## 동적으로 문자열 처리하기.
1. 일괄적인 범위의 메모리를 모두 특정한 값으로 설정하기 위해서는
    - `memset()`을 사용함
2. `memset(포인터 값, 크기);`
3. 한 바이트씩 값을 저장하므로 문자열 배열의 처리방법과 흡사
4. 따라서 memset()함수는 <string.h> 헤더에 선언되어있음.


```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    char *a = malloc(100); //100bytes, 1개 char 100개
    memset(a, 'A', 100);// equals => memset(a, 65, 100);
    for (int i = 0; i <100; i++){
        printf("%c\n", a[i]);
    }
    return 0;
}
```

- 결과로 A가 100번 출력됨.

## 2차원 배열을 동적 할당을 이용해 구현

```c
// 2차원 배열을 포인터 및 동적 할당을 이용해 구현


#include <stdio.h>
#include <stdlib.h>

int main(void){
    int** p = (int**)malloc(sizeof(int*) * 3);
    //이중 포인터, '행'에 대한 포인터 배열을 선언 (3개의 원소)
        for (int i = 0; i < 3; i++){ //각 행에 대해서
            *(p + i) = (int*)malloc(sizeof(int)*3); // i는 0 ~2 즉 각 행에 대해서 3개의 열에 대한 포인터를 생성해줌.
        }
        for (int i = 0; i < 3 ; i++){
            for (int j = 0 ; j < 3 ; j++) {
                *(*(p+i) + j) = i * 3 + j;
                //각 행의 열에 데이터를 넣어줌..
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
```