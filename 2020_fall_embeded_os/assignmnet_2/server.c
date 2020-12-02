/*
한국산업기술대학교 임베디드 시스템과 2015146007 김세환
임베디드 운영체제 과목 P2P Server Client Implementaion Source Code
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h> //for posix thread
#include <signal.h>  //for signal handler.
#include <fcntl.h>
//for custom functions.
#include "common.h" //macro 상수 define
#include "my_ip.h" // 불필요.
#include "list_func.h" //실행파일이 수행중인 디렉터리의 파일 목록을 파일로 만드는 함수 구현되어있음

//macro
#define SERV_IP "127.0.0.1" // 서버의 로컬 호스트 주소를 define
#define SERV_PORT 4140      //서버의 포트 번호를 define
#define BACKLOG 10
#define MAXLINE 512 //버퍼의 사이즈.

void recv_file(void); //각 클라이언트로부터 파일을 recv 하는 로직 함수화 필요

int main()
{
    int cmdstat;
    int sockfd, new_fd; //server 호스트의 소켓 파일디스크립터 및 새로운 연결을 정의할 new_fd
    int file_size; //파일의 사이즈, 미사용중
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    unsigned int sin_size;
    char file_name[MAXLINE]; //파일의 이름 -> 서버에서 유저별로 관리하기 위함
    char server_file_path[MAXLINE] = "./data/server_"; //각 유저별로 서버에 파일을 따로 저장함.
    //서버 코드가 돌아가는 디렉터리의 하위 폴더인 data 밑에 저장함

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
                int token = 0;
                token = authenticate(new_fd, id, pw);
                if (token == USER1_LOGIN)
                {
                    memset(buf, 0, sizeof(MAXLINE));
                    *(int *)&buf[0] = 1; //user1 인증 성공 정보를 보내기 위함(token)
                    send(new_fd, buf, sizeof(buf), 0);
                    //1이라는 정수를 전송해서 user1 로그인이 성공했음을 클라이언트에게 알림
                    //이제 파일을 전송받기위해 대기.
                    read(new_fd, file_name, MAXLINE);
                    printf("client will sent this file %s \n", file_name);//먼저 이 때 클라이언트가 파일 이름을 보내줄 것
                    strcat(server_file_path, file_name);//server_user1_file_list.lst 라는 이름으로 파일 관리.
                    int fd = 0; //fd를 열어놓음
                    fd = open(server_file_path, O_CREAT | O_RDWR | O_TRUNC,  S_IRWXU | S_IRWXG |  S_IWGRP |  S_IRWXO); //읽기쓰기 및 덮어쓰기, 실행권한
                    //기존에 user의 파일이 있을경우 업데이트를 위해 항상 접속하면 새로 작성한다.
                    //파일 수신 로직
                    int n_bytes = 0;
                    while ((n_bytes = read(new_fd, buf, MAXLINE)) > 0)
                    {
                        write(fd, buf, n_bytes);
                        printf("%s was receive\n n_bytes : %d ", buf, n_bytes);
                        if (n_bytes < MAXLINE){
                            printf("file receive done. \n");
                            close(fd);
                            break;
                        }
                    }
                    //파일 수신이 끝난 뒤 파일 기술자 닫음.
                    //파일 수신 이후 main loop 진입 필요
                    //사용자가 파일 목록을 요청하면
                    //임시파일로서 특정 디렉터리에 있는 파일들을 조합하고
                    //그 데이터를 사용자에게 전송해준 이후에 삭제하는 로직이 필요 할 듯.
                    close(fd);
                   //메인 로직, 클라이언트로부터 명령어를 전달받아 다양한 로직을 수행함. 
                    for(;;){
                        printf("server is wating for client's command.....\n");
                        read(new_fd, buf, MAXLINE);
                        printf("client send this command %s \n", buf);
                        if(strcmp("hello", buf) == 0){
                            printf("server get hello");
                            for(int i = 0; i<10; i++){
                                fputs("..", stdout);
                            }
                            strcpy(buf, "you said helo ?");
                            send(new_fd, buf, MAXLINE, 0);
                        }
                        else if(strcmp("exit", buf) == 0){
                            printf("client conenct close !\n");
                            strcpy(buf, "exit");
                            send(new_fd, buf, MAXLINE, 0);
                            break;
                        }
                        else if(strcmp("show", buf) == 0){
                            printf("user%d requested file list ... \n", token);
                            //파일디스크립터를 연다. data 디렉터리에 갖고있는 파일 목록을 확인하고
                            //해당 파일들을 순서대로 이어붙여서 임시 파일 생성
                            //임시파일 생성 후 클라이언트에게 전달
                            //클라이언트는 이 파일을 확인 한다.
                            //서버는 이 파일을 유지하다가, 커넥션이 종료될때 삭제한다.
                            //파일명은 user1_request.lst 로 만든다.
                        }
                        else {
                            printf("thre is no command like that ! \n");
                            strcpy(buf, "exit");
                            send(new_fd, buf, MAXLINE, 0);
                            break;
                        }
                    }
                    close(new_fd);
                    break;
                }
                else if (token == USER2_LOGIN)
                {   
                    memset(buf, 0, sizeof(MAXLINE));
                    *(int *)&buf[0] = token; //user2 인증 성공 정보를 보내기 위함
                    send(new_fd, buf, sizeof(buf), 0);
                    read(new_fd, file_name, MAXLINE);
                    printf("client will sent this file %s \n", file_name);
                    strcat(server_file_path, file_name);
                    int fd = 0;
                    fd = open(server_file_path, O_CREAT | O_RDWR | O_TRUNC,  S_IRWXU | S_IRWXG |  S_IWGRP |  S_IRWXO); //읽기쓰기 및 덮어쓰기, 실행권한
                    int n_bytes = 0;
                    while ((n_bytes = read(new_fd, buf, MAXLINE)) > 0)
                    {
                        write(fd, buf, n_bytes);
                        printf("%s was receive\n n_bytes : %d ", buf, n_bytes);
                    }
                    printf("file receive done. \n");
                    close(new_fd);
                    close(fd);
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