# 조건문, 반복문, 함수

- IF문
    - IF문 내부의 조건을 검사해 프로그램의 진행 경로를 결정한다
    - IF문은 조건의 개수가 많지 않을 때 사용하는 것이 유리하다

```c

#include <stdio.h>

void add(int a, int b, int *sum) {
    *sum = a + b;
}

int main(void) {
    printf("손님이 몇명 왔나요 ");
    int a;
    scanf("%d", &a);
    if ( a == 1 || a  == 2) {
        printf("2인석 \n");
    }
    else if (a == 3 || a == 4 ) {
        printf("4인석\n");
    }
    else {
        printf("대형석\n");
    }
    return 0;
}

```


- switch 문
    - 다양한 조건이 존재 할 때 사용하면 소스코등를 짧게 유지가 가능합니다.

```c
int main(void) {
    char score;
    printf("학점을 입력하시오");
    scanf("%c", &score);
    
    switch (score) {
        case 'A':
            printf("A학점입니다.\n");
            break;
        case 'B':
            printf("B학점 입니다. \n");
            break;
        case 'C':
            printf("C학점 입니다. \n");
            break;
        default:
            printf("학점을 제대로 입력하세요\n");
            break;
    }
    return 0;
}
```

- switch 문은 조건에 부합하는 경우 아래쪽 case도 모두 만족시킵니다.
- 따라서 일반적인 경우에 case 문 마지막에 break;를 삽입합니다.
- switch 문에는 char, int, long, double 등의 자료형 사용 가능하다.

## 요약

- 조건의 개수가 적을 땐 if문
- 조건의 개수가 많으면 case 문을 쓰는것이 편하다고 한다.

