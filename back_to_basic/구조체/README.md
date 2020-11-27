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

