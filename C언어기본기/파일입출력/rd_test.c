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