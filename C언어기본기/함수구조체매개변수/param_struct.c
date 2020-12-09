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