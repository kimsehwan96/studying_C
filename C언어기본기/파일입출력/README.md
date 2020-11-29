# 파일입출력

1. 파일 입출력 변순 FILE 포인터 변수로 선언
2. 파일을 열떄는 fopen
3. 파일 닫을떄는 fclose

## fopen
- 파일 열기 함수인 fopen()함수에는 파일 경로와 접근 방식 설정 가능
- r, w, a 제일 많이 사용
    - r 읽기 모드
    - w 쓰기모드(있으면 덮어쓰기)
    - a 파일에 접근해서 데이터를 뒤부터 기록

- 파일 입출력에서는 
    - fprintf(파일포인터, 서식, 형식지정자);
    - fscanf(파일포인터, 서식, 형식지정자);

- 파일을 열었으면 꼭 닫아야 한다.
    - 파일 열때 파일 포인터를 사용하고, 이거 동적할당 된거임

```c
#include <stdio.h>

int main(void){
    char s[20] = "Hello world";
    FILE *fp;
    fp = fopen("temp.txt", "w");
    fprintf(fp, "%s\n", s);
    fclose(fp);
    return 0;
}
```


## 구조체 포인터 및 포인터 연산 및 파일입출력 예제

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int score;
} Student;

int main(void){
    int n, sum = 0;
    FILE *fp;
    fp = fopen("input.txt", "r");
    fscanf(fp, "%d", &n); //정수를 읽어 n에 기록
    //Student 구조체 배열 포인터를 선언해보장
    Student *students = (Student*)malloc(sizeof(Student) *n); //n명의 학생에 대한 구조체 포인터 배열선언
    for (int i = 0; i < n; i ++){
        fscanf(fp, "%s %d", &((students + i)->name), &(students + i)->score); //scanf -> 주소를 불러줘야하징
        printf("%s %d\n", (students + i)->name, (students + i)->score);
    }
    return 0;
}
```


#### 평균 구하기 및 메모리 할당 해제

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int score;
} Student;

int main(void){
    int n, sum = 0;
    FILE *fp;
    fp = fopen("input.txt", "r");
    fscanf(fp, "%d", &n); //정수를 읽어 n에 기록
    //Student 구조체 배열 포인터를 선언해보장
    Student *students = (Student*)malloc(sizeof(Student) *n); //n명의 학생에 대한 구조체 포인터 배열선언
    for (int i = 0; i < n; i ++){
        fscanf(fp, "%s %d", &((students + i)->name), &(students + i)->score); //scanf -> 주소를 불러줘야하징
        printf("%s %d\n", (students + i)->name, (students + i)->score);
    }
    for (int i = 0; i < n; i ++){
        sum += (students + i)->score;
    }
    free(students);
    printf("sum : %f", (float)(sum/n));
    fclose(fp);
    return 0;
}
```

