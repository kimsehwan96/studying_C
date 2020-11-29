# 구조체
- 여러개의 변수를 묶어 하나의 객체를 표현하고자 할 때 사용함
- 캐릭터, 몬스터 ,학생, 좌표 등 객체를 모두 프로그래밍 언어를 이용해 표현할 수 있다.

```c
#include <stdio.h>
#include <string.h>

struct Student {
    char studentId[20];
    char name[10];
    int grade;
    char major[51];
};

int main(void){
    struct Student s;
    strcpy(s.studentId, "2015146007");
    strcpy(s.name, "김세환");
    s.grade = 4;
    strcpy(s.major, "전자공학");

    printf("%s\n", s.studentId);
    printf("%s\n", s.name);
    printf("%d\n", s.grade);
    printf("%s\n", s.major);

    return 0;
}
```


## 구조체의 정의와 선언
- 하나의 구조체 변수만을 사용하는 경우 정의와 동시에 사용 가능
- 이 경우 변수는 전역변수로 사용된다,.

```c
struct Student {
    char studentId[20];
    char name[10];
    int grade;
    char major[51];
} s; //s는 전역변수 정의와 동시에 사용
``` 

- 선언과 동시에 중괄호를 이용해 초기화 가능 !

```c
#include <stdio.h>
#include <string.h>

struct Student {
    char studentId[20];
    char name[10];
    int grade;
    char major[51];
};

int main(void){
    struct Student s = {"2015146607", "kim", 4, "전자공학"};

    printf("%s\n", s.studentId);
    printf("%s\n", s.name);
    printf("%d\n", s.grade);
    printf("%s\n", s.major);

    return 0;
}
```


## 더 짧게 구조체 정의하기

- typedef를 이용해 더 짧게 사용 가능

```c
typedef struct Student{
    char studentId[20];
    char name[10];
    int grade;
    char major[51];    
} Studnet;

int main(void){
    Student s; //이렇게 struct 안붙이고 사용 가능
}
```

### 구조체 포인터 변수

- 구조체가 포인터 변수로 사용되는 경우 내부 변수 접근시 -> 를 사용 (짱 많이 본 케이스)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char studentId[20];
    char name[10];
    int grade;
    char major[51];
} Student;

int main(void){
    Student *s = malloc(sizeof(Student));
    strcpy(s->studentId, "2015146007");
    strcpy(s->name, "김세환");
    s->grade = 4;
    strcpy(s->major, "전자공학");

    printf("%s\n", s->studentId);
    printf("%s\n", s->name)a;
    printf("%d\n", s->grade);
    printf("%s\n", s->major);

    return 0;
}
```


### 구조체의 멤버가 포인터일때 역참조 하기
- 구조체의 멤버가 포인터일때 역참조를 하려면 맨 앞에 * 을 붙이면 된다.
- *구조체변수.멤버
- *구조체포인터->멤버

```c
#include <stdio.h>
#include <stdlib.h>

struct Data {
    char c1;
    int *numPtr;
};

int main(void){
    int num1 = 10;
    struct Data d1;
    struct Data *d2 = (struct Data*)malloc(sizeof(struct Data));
    d1.numPtr = &num1;
    d2->numPtr = &num1;
    printf("%d\n", *d1.numPtr);     // 10: 구조체의 멤버를 역참조
    printf("%d\n", *d2->numPtr);    // 10: 구조체 포인터의 멤버를 역참조

    d2->c1 = 'a';
    d1.c1 = 'b';
    printf("%c\n", (*d2).c1);
    printf("%d\n", *(*d2).numPtr);
    printf("%c\n", ((struct Data*)&d1)->c1);
    //(struct Data*)&d1 이렇게하면 구조체 포인터처럼 쓸 수 있나봄
    //그래서 ((struct Data*)&d1)->c1 이렇게 멤버에 접근 가능
    free(d2);
}

```