#include <stdio.h>
#include <string.h>

struct Person {
    char name[20];
    int age;
    char address[100];
};

void setPerson(struct Person *p){
    strcpy(p->name, "바꿔버리기");
    p->age = 50;
    strcpy(p->address, "마유로 376");
}

int main(void) {
    struct Person p1;
    strcpy(p1.name, "김세환");
    strcpy(p1.address, "사성로 103번길 14");
    setPerson(&p1);
    printf("이름 : %s \n", p1.name);
    printf("나이 : %d \n", p1.age);
    printf("주소 : %s \n", p1.address);

    return 0;
}