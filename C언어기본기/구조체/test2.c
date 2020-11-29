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