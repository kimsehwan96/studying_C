# 함수에서 구조체 매개변수 사용하기;

- 함수에서 전달해야 할 매개변수가 많을때는 어떻게 하냐

- 만약 변수들을 구조체로 묶을 수 있다면

```c
반환값자료형 함수이름(struct 구조체이름 매개변수)
{
}
```

```c
#include <stdio.h>
#include <string.h>

struct Person {
    char name[20];
    int age;
    char address[100];
};

void printPerson(struct Person p) {
    printf("이름 : %s \n", p.name);
    printf("나이 : %d \n", p.age);
    printf("주소 : %s \n", p.address);
}

int main(void) {
    struct Person p;
    strcpy(p.name, "sehwan kim");
    strcpy(p.address, "사성로 103번길 14 106동");
    p.age = 25;

    printPerson(p);
    return 0;
}
```

- 함수를 호출할 때 구조체 변수를 넣어주면 구조체 변수의 모든 멤버가 매개변수로 복사됩니다.
- 다만 구조체 크기가 커지면 커질수록 공간이 더 필요하니까
- 아예 메모리 접근해서 하자 이거지 (복사 하지 말고)



### 구조체 포인터 매개변수 활용하기

```c
반환값자료형 함수이름(struct 구조체이름 *매개변수)
{
}
```

