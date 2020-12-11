#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct packet{
    char name[20];
    int idx;
};

void test_func(struct packet *pac, int idx);

int main(void){
    struct packet *pac = (struct packet *)malloc(sizeof(struct packet));
    test_func(pac, 65);
    printf("idx : %d\n", pac->idx);
    printf("name : %s\n", pac->name);
    return 0;
}

void test_func(struct packet *pac, int idx){
    int temp = 6;
    char temp_char[20] = "Hello World !";
    pac->idx = temp;
    strcpy(pac->name, temp_char);
}