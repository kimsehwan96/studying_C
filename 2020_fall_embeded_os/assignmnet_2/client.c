#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "common.h"

#define SERV_IP "127.0.0.1"
#define SERV_PORT 4140

void auth_request(int fd, char* id, char* pw, char buf[BUFSIZE]){
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
    read(fd, buf, BUFSIZE);
    printf("\n%s", buf);
}

int main(void){
    int sockfd;
    struct sockaddr_in dest_addr;
    int rcv_byte;
    char buf[512];
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
    auth_request(sockfd, id, pw, buf);

    close(sockfd);

    
}