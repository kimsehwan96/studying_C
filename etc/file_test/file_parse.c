#include <stdio.h>

int main(void){
    FILE *stream;
    stream = fopen("test.file", "r+"); //test.file을 염.

    int idx;
    char user[10];
    char ip[60];
    int port;
    char fn[100];

    while(fscanf(stream, "%d : %s %s %d %s", &idx, user, ip, &port, fn) > 0){
        printf("-------------------------- \n");
        printf("this is idx : %d \n", idx);
        printf("this is user : %s \n", user);
        printf("this is ip : %s \n", ip);
        printf("this is port : %d \n", port);
        printf("this is fn : %s \n", fn);
        printf("-------------------------- \n");       
    }
    fclose(stream);
    return 0;
    
}