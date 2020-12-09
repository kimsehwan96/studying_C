# 함수

```c
반환값자료형 함수이름(){
    //코드
    return 반환값;
}
```

### 포인터 반환하기

```c
반환값자료형 *함수이름(){
    return 반환값;
}
```

- 아래 코드는 잘못된 코드임

```c
#include <stdio.h>

int *ten(){
    int num1 = 10; //num1은 지역변수

    return &num1; //함수에서 지역 변수의 주소를 반환하는 것은 잘못된 방법
}
```

- 지역 변수의 주소를 반환하는 것은 오류임.

- 포인터를 반환하려면 malloc으로 메모리 할당한 뒤 반환하기

```c
#include <stdio.h>
#include <stdlib.h> //malloc, free

int *ten() {
    int *numPtr = malloc(sizeof(int)); //int 크기만큼 동적 메모리 할당

    *numPtr = 10; //역참조로 10을 저장

    return numPtr;  //포인터 반환, malloc으로 할당하면 함수가 끝나도 사라지지 않는다.
}

int main(void){
    int* numPtr;

    numPtr = ten();//호출값을 numPtr 에 저장한다.
    printf("%d\n", *numPtr); //10 출력. 안전함

    free(numPtr); //다른 함수에서 할당한 메모리라도 반드시 해제.

    return 0;
}
```

- 문자열 반환해보기

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *helloLitreal(void) //char 포인터를 반환하는 함수임
{
    char *s1 = "Hello World";
    return s1; //문자열은 메모리에 저장되어있으므로 사라지지 않는다.
}

char *helloDynamicMemory() {
    char *s1 = (char *)malloc(sizeof(char)*20);//char 20개 크기만큼 할당
    strcpy(s1, "Hello World ! ");
    return s1;
}
```

### void 포인터 반환하기

- 반환값의 자료형을 정하지 않고 꺼내오고 싶을때 사용

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *allocMemory(void){
    void *ptr = malloc(100); //100바이트 할당
    
    return ptr; //void 포인터 반환
}

int main(void){
    char *s1 = allocMemory(); //void 포인터를 char포인터에 넣어 문자열처럼 사용
    strcpy(s1, "Hello World !");
    printf("%s \n", s1);
    free(s1);

    int *numPtr1 = allocMemory();//void 포인터를 int 포인터에 넣어서 정수 배열처러 사용
    numPtr1[0] = 10; //첫번째 요소에 10 저장
    numPtr1[1] = 20; //두번째 요소애 20저장

    printf("%d %d \n", numPtr1[0], numPtr1[1]); //10, 20
    free(numPtr1);

    return 0;
}
```


- void 포인터는 강제형변환을 하지 않아도 다양한 형태의 포인터에 넣을 수 있다.


### 포인터 매개변수

```c
#include <stdio.h>

void swapNumber(int *first, int *second) {
    int temp;

    temp = *first;
    *first = *second;
    *second = temp;
}

int main() {
    int num1 = 10;
    int num2 = 20;

    swapNumber(&num1, &num2);
    printf("%d %d\n", num1, num2);

    return 0;
}
```

- 함수 밖에서 num1과 num2의 값이 바뀐것을 알 수 있다.
- 메모리에 접근해서 바꾸기 때문에 가능한 것 !!

### void 포인터 매개변수
- void 포인터 매개변수를 사용하면 자료형 변환을 하지 않아도 모든 자료형을 함수에 넣을 수 있다.
- char, int, float 형을 매개변수로 받아서 값을 바꿔보기.

```c
#include <stdio.h>

enum TYPE {
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT
};

void swapValue(void *ptr1, void *ptr2, enum TYPE t) {
    //반환값 없음, void 포인터 매개변수 두개와
    //변수의 자료형을 알려주기 위한 열겨형을 받음

    switch(t){
        case TYPE_CHAR:
        {
            char temp;
            temp = *(char *)ptr1;
            *(char *)ptr1 = *(char *)ptr2;
            *(char *)ptr2 = temp;
            break;
        }
        case TYPE_INT:
        {
            int temp;
            temp = *(int *)ptr1;
            *(int *)ptr1 = *(int *)ptr2;
            *(int *)ptr2 = temp;
            break;
        }
        case TYPE_FLOAT:
        {
            float temp;
            temp = *(float *)ptr1;
            *(float *)ptr1 = *(float *)ptr2;
            *(float *)ptr2 = temp;
            break;
        }
    }
}

int main(void){
    char c1 = 'a';
    char c2 = 'b';
    swapValue(&c1, &c2, TYPE_CHAR);
    printf("%c %c\n", c1, c2);

    int num1 = 10;
    int num2 = 20;
    swapValue(&num1, &num2,TYPE_INT);
    printf("%d %d\n", num1, num2);

    float num3 = 1.2344f;
    float num4 = 5.3132f;
    swapValue(&num3, &num4, TYPE_FLOAT);
    printf("%f %f\n", num3, num4);

    return 0;
}
```


### 이중 포인터 매개변수 사용

- 함수에서 포인터를 얻어오려면 어떻게 해야하는가.
- 함수에 포인터를 넘겨주고 메모리를 할당해보는 테스트를 먼저 해보자.

```c
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
```

- 위 코드는 메모리 주소를 받아서, 받은 메모리주소부터 동적할당을 해줠려고 하는 코드다.
- 근디 ptr은 함수 스코프를 넘어가면 날아가니까 세그폴트 나옴.

