# 반 복 문

- For 문
    - For문 내부의 조건에 부합하면 계속해서 특정한 구문을 실행
    - 반복문을 탈출하고자 하는 위치에 break 구문 삽입

```c

for(초기화; 조건; 반복 끝 명령어) {
    //반복적으로 실행하는 로직
}

```

```c
int main(void) {
    for(int i=0; i<=100; i++){
        printf("%d\n", i);
    }
    return 0;
}
```

*1부터 N까지 구하기*

```c
int main(void) {
    int n, sum = 0;
    printf("n을 입력하세요");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        sum = sum + i;
    }
    printf("result : %d\n", sum);
    return 0;
}
```


- 무한 루프
    - 종료 조건 없이 한없이 반복되는 반복문
    - 일부러 발생 시키는 경우도 있지만...
    - 보통은 개발자의 실수로 인해 발생

```c

for (초기화; 조건; 반복 끝 명령어){
    // 조건이 항상 참인 경우 무한 루프 발생
}
```

```c
int main(void) {
    int sum = 0;
    for(; 1;){
        int x;
        scanf("%d", &x);
        if (x == -1) break;
        sum = sum + x;
    }
    printf("result : %d\n", sum);
    return 0;
}
```

- -1이 입력 될 때 까지 더하는 코드이다. 
- `for(; 1;)` 이런식으로 많이 쓰는걸 봄 (break를 호출하기 전까지 무한 루프)
- `if (조건식) break;` 이렇게 인라인? 이라구하나.. 이렇게도 표현 가능

- WHILE문
    - WHILE문의 조건에 부합하면 계속해서 특정한 구문 실행
    - 반복문 탈출하고자 하는 위치에 break 구문 삽입

```c
while (조건) {
    // 반복적으로 실행할 부분
}

```c
int main(void) {
    int n;
    char c;
    scanf("%d %c", &n, &c);
    while(n--){
        printf("%c\n", c);
    }
    return 0;
}
```

*특정 문자 N번 출력하기*

```c
#include <stdio.h>

int main(void) {
    for (int i=2; i<=9; i++){
        printf("-----------\n");
        for (int v=1; v<=9; v++){
            printf("%d x %d = %d\n", i, v, i*v);
        }
    }
    return 0;
}
```
*구구단*

```c
#include <stdio.h>

int main(void) {
    int i = 1;
    while (i<=9){
        int j = 1;
        while(j<=9){
            printf("%d x %d = %d\n", i, j, i * j);
            j++;
        }
        i++;
    }
    return 0;
}
```

- 똑같이 구현
    - 나는 하다가 생각없이 i++, j++를 안 넣어줘서 무한루프에 빠졌었음
