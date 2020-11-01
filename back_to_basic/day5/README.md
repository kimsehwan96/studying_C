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

fflush는 윈도우서만 동작 리눅스 동작 x(macos 동일..)

