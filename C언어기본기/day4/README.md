# function

- 함수는 입력을 받아 출력을 한다.
- 특정한 기능에 대한 소스코드가 반복되는 것을 줄이도록 해준다.

```c
#include <stdio.h>

void dice(int input){
    printf("throw dice! %d\n", input);
}

int add(int a, int b){
    return a + b;
}

int main(void) {
    int x = 10;
    int y = 20;
    printf("%d\n", add(x,y));
    return 0;
}

```

## 재귀 함수
- 자기 자신을 호출하는 함수임. (깊이를 정해주거나 한정지어줘야함)

```c
#include <stdio.h>

int factorial(int a) {
    if (a == 1) return 1; //종료조건
    else return a * factorial(a - 1);
}

int main(void) {
    printf("%d\n", factorial(5));
    return 0;
}

```

`factorial(5)`의 계산 과정
- return 5 * factortial(4)를 리턴하고, factorial(4)를 계산하기위해서
- return 4 * factorial(3)을 리턴, 호출
- return 3 * factorial(2)를 리턴, 호출
- return 2 * factorial(1)를 리턴 호출
- factorial(1)은 1을 리턴.

* 각 재귀 호출은 스택 프레임(메모리에) 부가 공간을 필요로 함
    - 무한 재귀에 들어가게 되면 메모리 용량을 초과해서 스택 오버플로우 발샹

재귀 사용 알고리즘 예
- 피보나치 수열, 팩토리얼
- 병합 정렬, 퀵 정렬
- 이진 검색
- 트리 탐색, 중위, 전위, 후위 등 여러 트리 문제들
- 그래프 탐색, 깊이 우선 탐색과 너비 우선 탐색
- Dynamic programming(DP)
- 분할 정복
- 하노이의 탑
- 백트래킹 등

## 배열

```c
#include <stdio.h>

int main(void) {
    int a[10] = {5,4,3,1,6,8,9,11,13,43};
    for (int i=0; i<10; i++){
        printf("%d\n", a[i]);
    }
    return 0;
}

```

```c
#include <stdio.h>
#include <limits.h>

int main(void) {
    int a[10] = {5,4,3,1,6,8,9,11,13,43};
    int i, maxValue = INT_MIN;
    for (i=0; i<10; i++){
        if(maxValue < a[i]) maxValue = a[i];
    }
    printf("max Value %d\n", maxValue);
    return 0;
}

```
-> 배열에서 최댓값 찾는 문제
