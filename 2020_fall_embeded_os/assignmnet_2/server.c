#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h> //for posix thread
#include <signal.h> //for signal handler.
#include <fcntl.h>
//for custom functions.
#include "common.h"
#include "my_ip.h"
#include "list_func.h"

//macro
#define SERV_IP "127.0.0.1" // 서버의 로컬 호스트 주소를 define
#define SERV_PORT 4140            //서버의 포트 번호를 define
#define BACKLOG 10
#define CMSUC 1 //handler 성공
#define CMFAIL 0 //handler 실패
#define CMEXIT -1 //hanlder exit 요청
#define CMDLS 10
#define MAXLINE 512
#define SERV_FILE "users_file.lst"

void recv_file(void);//각 클라이언트로부터 파일을 recv 하는 로직 함수화 필요

int main()
{
    int cmdstat;
    int sockfd, new_fd; //server 호스트의 소켓 파일디스크립터 및 새로운 연결을 정의할 new_fd
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    unsigned int sin_size;
    char file_name[MAXLINE];
    int file_size;

    //for server concurrency, we will fork server process with each connection request.
    pid_t childpid;
    int rcv_byte;
    char *buf = (char *)malloc(MAXLINE);
    char id[20];
    char pw[20];
    char msg[512];

    int val = 1;

    //socket TCP file descirptor
    //check sockfd condition
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
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

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&val, sizeof(val)) < 0)
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
    memset(pw, 0, sizeof(pw));

    sin_size = sizeof(struct sockaddr_in);

    for (;;)
    {
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);

        if (new_fd < 0)
        {
            perror("bind error ");
            exit(1);
        }
        printf("Connection accept from %s\n", inet_ntoa(their_addr.sin_addr));

        if ((childpid = fork()) == 0)
        { //child process
            //close(sockfd); 더이상 필요하지 않을때 (프로그램 서버측 종료시에) 종료하는게 맞음
            for (;;)
            {
                printf("accept ok \n");

                if (authenticate(new_fd, id, pw) == USER1_LOGIN)
                {   /*
                    *some logic should be in here for user1 (callback function)
                    *until client send "exit", this process gonna be doing.
                    *TODO: 클라이언트의 request 명령에 따라서 서버측 작업을 수행한다.
                    * 클라이언트가 수행하고 싶은 명령 목록을 나누어보자
                    * 1. 리스트 전송
                    * 2. 서버측 파일 리스트 확인
                    * 3. 특정 파일 요청 
                    * 4. 종료
                    * 우선 1,2,4만 수행해보자.
                    */
                    memset(buf, 0 ,sizeof(MAXLINE));
                    *(int *)&buf[0] = 1;
                    send(new_fd, buf, sizeof(*buf), 0);
                    //1이라는 정수를 전송해서 user1 로그인이 성공했음을 클라이언크에게 알림
                    //이제 파일을 전송받기위해 대기.
                    //먼저 이 때 클라이언트가 파일 이름을 보내줄 것이다. (저장할 파일 이름 버퍼에 저장)
                    //fd를 열어놓음
                    int fd = 0;
                    fd = open(SERV_FILE, O_CREAT | O_RDWR | O_APPEND, 777); //읽기쓰기 및 이어쓰기.
                    //file_name read
                    read(new_fd, file_name, MAXLINE);
                    printf("client will sent this file %s \n", file_name);
                    //파일 수신 로직
                    int n_bytes = 0;
                    while((n_bytes = read(new_fd, buf, MAXLINE)) > 0){
                        write(fd, buf, n_bytes);
                        printf("%s was receive\n n_bytes : %d ", buf, n_bytes);
                    }
                    printf("file receive done. \n");
                    //파일 수신이 끝난 뒤 파일 기술자 닫음.
                    close(new_fd);
                    close(fd);
                    break;
                }
                else if (authenticate(new_fd, id, pw) == USER2_LOGIN)
                {
                    //some logic should be in here for user2 (callback function)
                    close(new_fd);
                    break;
                }
                else
                {
                    printf("there is no such that inofrmation id : %s pw : %s\n", id, pw);
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