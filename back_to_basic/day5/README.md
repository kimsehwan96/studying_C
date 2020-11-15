# 문자 및 버퍼

- 아스키 코드
    - 아스키 코드는 1바이트로 구성, 0~127까지 각 번호에 따라서 다른 문자를 표현

0 ~ 9 까지의 숫자는 48 ~ 57의 아스키 코드로 표현
A는 65
a는 97

```c
#include <stdio.h>

int main(void) {
    char a = 48;
    for (int i = 0; i<10; i++){
        printf("%c\n", a);
        a++;
    }
    return 0;
}

```

```c
#include <stdio.h>

int main(void) {
    char a = getchar();
    printf("%c\n", a);
    return 0;
}
```

*버퍼(getchar)를 이용한 입력*



### 입력 버퍼로 인해 생기는 잘못된 예

```c
#include <stdio.h>

int main(void) {
    int a;
    char c;
    scanf("%d", &a);
    printf("%d\n", a);
    scanf("%c", &c);
    printf("%c\n", c);
    return 0;
}
```
- 위 예제는 프로그램 실행하고, 정수를 입력하고 엔터를 치면 바로 정수만 출력하고 프로그램이 종료된다
- 왜냐면 56을 치고 엔터를 치게 되면, 56\n 의 입력 버퍼가 처리 된것이라, 56을 a에 저장 \n을 c에 저장하게 된 것.

- 남아있는 입력버퍼를 지우는 방식을 사용해야 한다.

```c
#include <stdio.h>

int main(void) {
    int a;
    char c;
    scanf("%d", &a);
    printf("%d\n", a);
    int temp;
    // temp에 getchar()를 통해 버퍼의 남은 요소를 하나 받고
    // 이것이 EOF가 아니거나, temp (이미 앞에서 getchar()로 받아서 temp그대로 씀)
    //temp가 '\n'이 아니면 입력을 멈추는 것, 즉 입력버퍼를 지운다.(temp = getchar())
    while((temp = getchar()) != EOF && temp != '\n') { }
    scanf("%c", &c);
    printf("%c\n", c);
    return 0;
}
```


```c
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
```

- setvbuf(파일포인터, 사용자지정입출력버퍼, 모드, 크기);
    - int setbuf(FILE *_STEAM, char *_Buffer, int _Mode, size_t_Size);
    - 설정 변경에 성공하면 0을 반환, 실패하면 0이 아닌 값을 반환

`setvbuf(stdout, NULL, _IOFBF, 10);`
- 표준 출력 stdout의 출력 버퍼를 10으로 설정했기 때문에, 버퍼 크기 10만큼 출력되고, 3초 뒤 비어져서 모두 출력
- 첫번째 인자인 파일 포인터(파일 스트림) stdin, stdout, stderr 등이 포함.
- 두번째 인자로는 입출력 버퍼로 사용할 배열(메모리)를 의미, NULL을 지정하면 내부적으로 버퍼 공간 생성
- 세번째 인자는 버퍼링 모드 
    - _IOFBF : Full buffering : 버퍼가 가득차면 버퍼를 비움
    - _IOLBF : Line buffering : \n을 만나거나 버퍼가 가득차면 비움
    - _IONOBUF: No Buffering : 버퍼를 사용하지 않음.

- 출력 버퍼를 강제로 비우는 함수
- fflush(파일포인터)
    - int fflush(FILE *_STREAM);
    - 성공하면 0, 실패하면 EOF(-1) 반환

fflush는 윈도우서(window visual studio),
리눅스나 macos는 안되는데, 리눅스 & macos는 gcc 컴파일러로 컴파일 하는데,, 이 컴파일러에서 해당 함수 지원을 안해준다고 하는 듯   
-> visual studio는 fflush를 확장해서 사용하는 것이라고 함.


### 문자열

#### 문자열과 포인터
1. 문자열 형태로 포인터를 사용하면, 포인터에 특정한 문자열의 주소를 넣게 됨.

```c
#include <stdio.h>

int main(void) {
    char *a = "Hello world";
    int c = 5;
    int *p;
    p = &c;
    printf("%s\n", a);
    printf("%p\n", a); //문자열 포인터에 담긴 변수(Hello wolrd)가 메모리 어떤 번지에서 부터 저장되는지
    printf("%p\n", &a); //포인터 변수의 저장 위치.
    printf("-------------\n");
    
    printf("%p\n", &c); // 정수형 변수의 메모리 위치
    printf("%p\n", &p); // 정수형 포인터의 메모리 위치
    return 0;
}
```

```console
Hello world
0x100003f8e
0x7ffeefbff4b0
-------------
0x7ffeefbff4ac
0x7ffeefbff4a0
```

* 개인적으로 궁금한 점
    - Hello world 라는 문자열 배열은 0x100000~~~ 이라는 위치에 저장되었는데
    - 포인터 변수, 정수형 변수등은 서로 비슷한 메모리 주소에 저장 되었다.
    - 배열은 일반적인 변수와 다른 영역(스택 /힙이라고 하는 것들)에 저장되는 것?

- 테스트 해보기.
```c
#include <stdio.h>

int main(void) {
    char *a = "Hello world";
    int intArray[] = {1,2,3,4,5,6,7};
    int c = 5;
    int *p;
    p = &c;
    printf("%s\n", a);
    printf("%p\n", a); //문자열 포인터에 담긴 변수(Hello wolrd)가 메모리 어떤 번지에서 부터 저장되는지
    printf("%p\n", &a); //포인터 변수의 저장 위치.
    printf("-------------\n");
    
    printf("%p\n", &c); // 정수형 변수의 메모리 위치
    printf("%p\n", &p); // 정수형 포인터의 메모리 위치
    printf("%p\n", intArray); // 배열 형태의 정수형 데이터들의 저장된 메모리 시작 위치
    return 0;
}
```

```console
Hello world
0x100003f64
0x7ffeefbff480
-------------
0x7ffeefbff47c
0x7ffeefbff470
0x7ffeefbff490
```
 
????

```c
#include <stdio.h>

int main(void) {
    char *a = "Hello world";
    int intArray[] = {1,2,3,4,5,6,7};
    char charArray[] = "hello";
    int c = 5;
    int *p;
    p = &c;
    printf("%s\n", a);
    printf("%p\n", a); //문자열 포인터에 담긴 변수(Hello wolrd)가 메모리 어떤 번지에서 부터 저장되는지
    printf("%p\n", &a); //포인터 변수의 저장 위치.
    printf("-------------\n");
    
    printf("%p\n", &c); // 정수형 변수의 메모리 위치
    printf("%p\n", &p); // 정수형 포인터의 메모리 위치
    printf("%p\n", intArray); // 배열 형태의 정수형 데이터들의 저장된 메모리 시작 위치
    printf("%s\n", charArray); //charArray에 담긴 문자열 출력
    printf("%p\n", &charArray); //charArray 문자형데이터들 배열의 시작 주소
    return 0;
}
```


```console
Hello world
0x100003f58
0x7ffeefbff480
-------------
0x7ffeefbff474
0x7ffeefbff468
0x7ffeefbff490
hello
0x7ffeefbff47a
```
???????????????? 대체 `char *a = "Hello world";` 저 문자열 배열은 다른 변수와 상당히 많이 다른 위치에 저장되는 이유가 무엇일까

이유 : 저 문자열을 읽기 전용으로 메모리 공간에 넣은뒤 그 위치를 처리  
이러한 문자열을 문자열 리터럴이라고 이야기 하며, 컴파일러가 알아서 메모리 주소를 결정.

- 검색 결과 이러한 상수, 리터럴은 메모리의 5가지 종류 영역(텍스트, 데이터, bss, 힙, 스택)중에서 텍스트 영역에 저장된다구 한다 !!
- 읽기 전용 영역

` char charArray[] = "hello";` 와 같은 경우는 수정이 가능하고, stack 영역에 저장된다. 
- 그니까 저 위에 주소 비슷한 놈들 다 스택 영역에 저장된거다.
* 실제 `const int test = 5;`로 상수 하나 만들고 찍어봤는데 스택 영역에 저장
    - 확인해보니, 실제로 문자열 리터럴 말고 다른 상수들은 stack영역에 저장된다고 이야기 한다.
        - 다만 컴파일러에서는 이 값을 변환시키려고 할 때 오류를 내보낸다고 함(바뀌면 안되니까.)

* scanf() 함수는 공백을 만날 때 까지 입력을 받지만, gets()함수는 공백까지 포함하여 한 줄을 입력 받는다.

```c
#include <stdio.h>

int main(void) {
    char a[100];
    gets(a); //배열상의 크기를 고려하지 않고 받기 때문에 unsafe하다.
    printf("%s\n", a);
    return 0;
}

```

<strong> 더 안전한 버전 </strong>

```c
#include <stdio.h>

int main(void) {
    char a[100];
    gets_s(a, sizeof(a)); // a의 사이즈 만큼 입력을 받겠다 100개만 입력 받겠다!
    printf("%s", a);
    return 0;
}

```

## 문자열 처리를 위한 다양한 함수

- `strlen()` : 문자열의 길이를 반환
- `strcmp()` : 문자열 1이 문자열 2보다 사전적으로 앞에있으먼 -1, 뒤에있으면 1을 반환
- `strcpy()` : 문자열을 복사한다.
- `strcat()` : 문자열 1에 문자열 2를 더한다 
- `strstr()` : 문자열 1에 문자열 2가 어떻게 포함디어있는지를 반환한다.

- strlen() 예제
```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char *a = "Kim se hwan";
    printf("문자열 길이 : %lu\n", strlen(a));
    return 0;
}
```

- 생각을 해보면... a라는 일종의 배열은 첫 주소부터 저장된 문자열들 + 1 (마지막 null 때문에) 만큼의 메모리에 저장되는거고.
- a[인덱스]로 접근하면 한글자 한글자씩도 출력이 가능하지 !


```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char *a = "Kim se hwan";
    //printf("문자열 길이 : %lu\n", strlen(a));
    for(int i = 0; i <= strlen(a); i++) {
        printf("%c\n", a[i]);
        printf("%p\n", &a[i]);
    }
    return 0;
}

```

```console
K
0x100003fa0
i
0x100003fa1
m
0x100003fa2
 
0x100003fa3
s
0x100003fa4
e
0x100003fa5
 
0x100003fa6
h
0x100003fa7
w
0x100003fa8
a
0x100003fa9
n
0x100003faa
 
0x100003fab
Program ended with exit code: 0
```

- for loop를 이용해서 각 배열의 인덱스로 접근해서 메모리 주소 찍어보고, 값도 찍은 결과물이다.

<strong> 문자열 리터럴은 바꾸지 못해도, 문자열 변수(배열)에 저장된 값은 바꿀 수 있다 !</strong>

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char *a = "Kim se hwan";
    printf("%s\n", a);
    printf("change string !\n");
    a = "Hello world";
    printf("%s\n", a);
    return 0;
}
```

```console
Kim se hwan
change string !
Hello world
Program ended with exit code: 0
```

- 여기서 a라는건 배열의 첫번째 주소를 의미한다!!!!!



### 문자열 처리 함수 실습

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char *a = "Kim se hwan";
    printf("%lu\n", strlen(a)); // strlen(a)는 반환이 unsigned long.
    return 0;
}

```


```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char *a = "Dd";
    char *b = "Cb";
    printf("%d\n", strcmp(a, b));
    return 0;
}

```

<strong> strcmp는 비교 대상 문자(a에 있는 문자열 중 첫번째)가(ASCII) 비교하려는 문자보다 사전 적으로 얼마나 큰지 리턴 <strong>
- 예를들어 A와 B를 비교하면 1, B와 A를 비교하면 -1, A와 C를 비교하면 3이 나온다.


```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char a[30] = "My name is ";
    char b[20] = "Kim se hwan\n";
    strcat(a, b);
    printf("%s",a);
    
    return 0;
}

```

- 문자열을 합치는 함수 strcat()이고, 리턴이 없는 프로시져다.
    - 앞의 문자열의 배열이 널널해야 오류가 안나네!!

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char a[20] = "I love you";
    char b[20] = "love";
    printf("%s",strstr(a, b));
    
    return 0;
}
```

- strstr(긴 문자열,짧은 문자열) 의 경우, 반환이 긴 문자열에서 매치되는 짧은 문자열의 시작 <strong>주소</string>를 리턴한다.
    - 즉 단순 출력하기만 하면 뒤에 문자열까지 모두 출력이 된다는 의미다.
    