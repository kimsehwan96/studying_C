# 전처리기

- include
    - #include <파일이름>
        - 시스템 디렉토리에서 파일을 검색
        - 운영체제마다 시스템 디렉토리의 경로가 다를 수 있음

- 매크로 전처리기
    - 프로그램 내에서 사용하는 상수나 함수를 매크로 형태로 저장하기 위해 사용
    - #define 이용.

```c
#include <stdio.h>

//define macro here
#define PI 3.141592
#define POW(x) (x * x)
#define ll long long
#define ld long double 
//자료형을 매우 짧게 정의해놓고 쓰는 경우가 많다.


int main(void){
    int a = 2;
    printf("%d\n", POW(a));
}

```


## 조건부 컴파일
- 조건부로 컴파일이 이루어지는 영역을 지정하는 기법
- 디버깅과 소스코드 이식을 목적
- 운영체제, 타겟디바이스(아키텍쳐?)에 따라 소스코드가 달라질 수 있음.

- temp.h 헤더 파일을 예를들자
    - 혹시나 이중으로 temp.h가 include 되거나 함수가 동일하게 정의되는 것을 ㅁ막자.
```c
#ifndef _TEMP_H_ //_TEMP_H_가 정의되있지 않으면
#define _TEMP_H_ //_TEMP_H_ 정의.
int add(int a, int b){
    return a + b;
}
#endif

```

## 파일 분할 컴파일
- 자신이 직접 라이브러리를 만들 때는 분할해서 만들자.


<strong> temp.h </strong>

```c
#ifndef _TEMP_H_ //_TEMP_H_가 정의되있지 않으면
#define _TEMP_H_ //_TEMP_H_ 정의.
int add(int a, int b);
#endif
```
<strong> temp.c </strong>

```c
#include "temp.h"
int add(int a, int b){
    return a + b
}
```

