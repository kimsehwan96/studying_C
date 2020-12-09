/*
한국산업기술대학교 임베디드 시스템과 2015146007 김세환
임베디드 운영체제 과목 P2P Server Client Implementaion Source Code
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h> //open, close 등 파일 디스크립터 사용을 위함
#include <errno.h>
#include "common.h"    //유저 인증 로직 및 macro 상수
#include "list_func.h" //내부 파일 리스트를 생성하는 함수
#include "my_ip.h"     //ip check 함수

#define SERV_IP "127.0.0.1"
#define SERV_PORT 4140
#define INIT_STATE 0
#define AFTER_STATE 1
#define SEG 1

extern int errno;

//서버와 인증 로직을 수행하기 위한 read, send, scanf 등의 함수를 하나의 flow로 함수화함
void auth_request(int fd, char *id, char *pw, char *buf)
{
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

int main(void)
{
    int sockfd, fd;
    int rcv_byte, file_size;
    int token = 0;
    struct sockaddr_in dest_addr;
    char *buf = (char *)malloc(BUFSIZE);
    char *msg = (char *)malloc(BUFSIZE);
    char *file_buf = (char *)malloc(SEG);
    char file_name[512];
    char id[20];
    char pw[20];
    int state = INIT_STATE;
    int len = BUFSIZE;
    FILE *write_sock_fp;
    FILE *read_sock_fp;
    ssize_t ret;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //socket fd

    if (sockfd == -1)
    {
        perror("socket");
        exit(1);
    }
    else
    {
        printf("socket is ok \n");
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(SERV_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    memset(&(dest_addr.sin_zero), 0, 8);
    if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }
    else
    {
        printf("connect ok\n");
    }
    auth_request(sockfd, id, pw, buf); //if user 1 success, we will get 1
    read(sockfd, buf, BUFSIZE);
    printf("this is token %d\n", *(int *)&buf[0]);
    token = *(int *)&buf[0];
    if (token == 1)
    { //유저 1 로그인 성공
        printf("login success user%d\n", token);
        mklistf("user1", "127.0.0.1"); //뒤에 인자(ip address)는 my_ip 헤더를 이용할 것.
        strcpy(file_name, "user1_file_list.lst");
        if ((fd = open("user1_file_list.lst", O_RDWR)) < 0)
        {
            perror("open() error !");
        }
        send(sockfd, file_name, BUFSIZE, 0);
        FILE *user_list_fp;
        user_list_fp = fdopen(fd, "r+");
        send_file(user_list_fp, sockfd);
        printf("sending file done ! \n");

        close(fd);
    }
    else if (token == 2)
    {
        printf("login success user%d\n", token);
        mklistf("user2", "127.0.0.1"); //뒤에 인자(ip address)는 my_ip 헤더를 이용할 것.
        strcpy(file_name, "user2_file_list.lst");
        if ((fd = open("user2_file_list.lst", O_RDWR)) < 0)
        {
            perror("open() error !");
        }
        send(sockfd, file_name, BUFSIZE, 0);
        FILE *user_list_fp;
        user_list_fp = fdopen(fd, "r+");
        send_file(user_list_fp, sockfd);
        printf("sending file done ! \n");

        close(fd);
    }
    else
    {
        printf("login failed.");
        exit(1);
    }

    for (;;)
    {
        printf("\nplz input your command user%d :", token);
        scanf("%s", buf);
        send(sockfd, buf, BUFSIZE, 0);
        if ((send(sockfd, buf, BUFSIZE, 0)) == -1)
        {
            perror("send error ! ");
        }
        printf("send result : %s", buf);
        read(sockfd, buf, BUFSIZE);
        printf("this msg was sent from server : %s \n", buf);

        if (strcmp(buf, "exit") == 0)
        {
            printf("connect done !");
            break;
        }

        else if (strcmp(buf, "list") == 0)
        {
            fputs("wait", stdout);
            for (int i = 0; i < 50; i++)
            {
                fputs(".", stdout);
                fflush(stdout);
                usleep(10000);
            }
            fputs("\n", stdout);
            print_recv_file(sockfd);
            printf("recv done !~!");
        }
        else {
            printf("%s\n", buf);
            printf("no meaning...\n");
        }
    }
    close(sockfd);
    free(buf);

    return 0;
}