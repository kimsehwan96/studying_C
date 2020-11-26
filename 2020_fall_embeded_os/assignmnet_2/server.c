#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//for custom functions.
#include "common.h"
#include "my_ip.h"
#include "list_func.h"

//macro
#define SERV_IP "220.149.128.100" // 서버의 로컬 호스트 주소를 define
#define SERV_PORT 4140            //서버의 포트 번호를 define
#define BACKLOG 10

int main()
{
    int sockfd, new_fd; //server 호스트의 소켓 파일디스크립터 및 새로운 연결을 정의할 new_fd
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    unsigned int sin_size;

    //for server concurrency, we will fork server process with each connection request.
    pid_t childpid;
    int rcv_byte;
    char buf[512];
    char id[20];
    char pw[20];
    char msg[512];

    int val = 1;

    //socket TCP file descirptor
    //check sockfd condition
    if ((sockfd = sokcet(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("serverf-socket() error occured");
        exit(1);
    }
    else
    {
        printf("server socket() sockfd is ok \n");
    }

    my_addr.sin_family = AF_INET; //address family is AF_INET

    my_addr.sin_port = htons(SERV_PORT);

    my_addr.sin_addr.s_addr = INADDR_ANY; //any address can accept

    memset(&(my_addr.sin_zero), 0, 8);

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&val, szieof(val)) < 0)
    {
        perror("setsockopt");
        close(sockfd);
        return -1;
    }

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == 1)
    {
        perror("bind error ");
        exit(1);
    }
    else
    {
        printf("server bind ok \n");
    }
    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("Listen error");
        exit(1);
    }
    else
    {
        printf("listen ok \n\n");
    }

    memset(id, 0, sizeof(id));
    memset(pw, 0, sizeop(pw));

    sin_size = sizeof(struct sockaddr_in);

    for (;;)
    {
        new_fd = accpet(sockfd, (struct sockaddr *)&their_addr, &sin_size);

        if (new_fd < 0)
        {
            perror("bind error ");
            exit(1);
        }
        printf("Connection accpet from %s\n", inet_ntoa(their_addr.sin_addr));

        if ((childpid = fork()) == 0)
        { //child process
            close(sockfd);
            for (;;)
            {
                prinf("accept ok \n");
                //send id, pw request msg and receive from client
                send(new_fd, ID_REQ, strlen(ID_REQ) + 1, 0); //strlen((char *)some_string +1) 인 이유는 Null 포함
                read(new_fd, id, sizeof(id));
                send(new_fd, PW_REQ, strlen(PW_REQ) + 1, 0);
                read(new_fd, pw, sizeof(pw));
                //유저가 입력한 내용을 서버에서 출력
                printf("===========================\n");
                printf("User Information\n");
                printf("id : %s  pw : %s \n", id, pw);
                printf("===========================\n");

                if (authenticate(id, pw) == USER1_LOGIN)
                {
                    printf("%s Login success \n", id);
                    send(new_fd, "LOGIN SUCCESS USER 1 \n", 512, 0);
                    //some logic should be in here for user1 (callback function)
                    close(new_fd);
                    break;
                }
                else if (authenticate(id, pw) == USER2_LOGIN)
                {
                    printf("%s Login success \n", id);
                    send(new_fd, "LOGIN SUCCESS USER 2 \n", 512, 0);
                    //some logic should be in here for user1 (callback function)
                    close(new_fd);
                    break;
                }
                else
                {
                    printf("there is no such that inofrmation id : %s pw : %s", id, pw);
                    send(new_fd, "LOGIN FAIL \n", 512, 0);
                    printf("Disconnected from %s\n", inet_ntoa(their_addr.sin_addr));
                    close(new_fd);
                    break;
                }
            }
        }
    }
    close(new_fd);
    close(sockfd);
}