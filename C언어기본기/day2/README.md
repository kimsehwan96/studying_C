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




```c
int main(void) {
    printf("학점을 입력하세요");
    char a;
    scanf("%c", &a);
    switch (a) {
        case 'A':
            printf("A 학점\n");
        case 'B':
            printf("B 학점\n");
        case 'C':
            printf("C 학점 \n");
        default:
            printf("학점을 바르게 입력하세요 \n");
    }
    return 0;
}
```

- 입력받은 학점에 따라 분기해서 출력하는 코드
    - B를 입력하먄 B, C 가 출력이 되는데
    - 조건에 맞는 부분 부터 밑으로 쭉 실행되나봄
    - 그래서 필요한게 `break`

```c

#include <stdio.h>
typedef unsigned char bool;
#define True 1
#define False 0

int main(void) {
    printf("월을 입력하세요");
    int a;
    scanf("%d", &a);
    switch (a) {
        case 1:
        case 2:
        case 3:
            printf("봄 \n");
            break;
        case 4:
        case 5:
        case 6:
            printf("여름\n");
            break;
        case 7:
        case 8:
        case 9:
            printf("가을\n"); break;
        case 10:
        case 11:
        case 12:
            printf("겨울\n"); break;
    }
    return 0;
}
```