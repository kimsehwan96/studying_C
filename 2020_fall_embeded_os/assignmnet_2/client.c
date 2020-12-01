#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "common.h"
#include "list_func.h" //내부 파일 리스트를 생성하는 함수
#include "my_ip.h" //ip check 함수

#define SERV_IP "127.0.0.1"
#define SERV_PORT 4140

void auth_request(int fd, char* id, char* pw, char *buf){
    read(fd, buf, BUFSIZE);
    printf("%s", buf);
    scanf("%s", id);
    send(fd, id, strlen(id) + 1, 0);
    memset(buf, 0, BUFSIZE);
    read(fd, buf, BUFSIZE);
    printf("\n%s", buf);
    scanf("%s", pw);
    send(fd, pw, strlen(pw) + 1, 0);
    memset(buf, 0, BUFSIZE);
}

int main(void){
    int sockfd;
    struct sockaddr_in dest_addr;
    int rcv_byte;
    char *buf = (char *)malloc(BUFSIZE);
    char id[20];
    char pw[20];

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //socket fd

    if (sockfd == -1){
        perror("socket");
        exit(1);
    }
    else {
        printf("socket is ok \n");
    }
    
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(SERV_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    memset(&(dest_addr.sin_zero), 0, 8);
    if(connect(sockfd, (struct sockaddr* )&dest_addr, sizeof(struct sockaddr)) == -1){
        perror("connect");
        exit(1);
    }
    else {
        printf("connect ok\n");
    }
    auth_request(sockfd, id, pw, buf); //if user 1 success, we will get 1
    memset(buf, 0, sizeof(BUFSIZE));
    read(sockfd, buf, sizeof(BUFSIZE));
    printf("%d", *(int *)&buf[0]);
    if (*(int *)&buf[0]==1){
        printf("login success");
        //login success logic here
        mklistf("user1", "127.0.0.1"); //뒤에 인자(ip address)는 my_ip 헤더를 이용할 것.
        //user1_file_list.lst 생성 완료, 이 파일을 서버에 전송해야 함.
        //sockfd를 통해 파일을 전송하는 로직 작성해야 함
        //1. 파일 이름을 먼저 전송한다
        //2. 파일의 크기를 전송한다.
        //3. EOF까지 파일을 char로 BUFSIZE에 최대한 담아서 보낸다.
    }
    else {
        printf("login failed.");
    }
    close(sockfd);
    free(buf);
}