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
#include <pthread.h>  //for posix thread
#include <signal.h>   //for signal handler.
#include <fcntl.h>    //for file handling
#include <sys/stat.h> //for file status
#include <dirent.h>
//for custom functions.
#include "common.h"    //macro 상수 define
#include "my_ip.h"     // 불필요.
#include "list_func.h" //실행파일이 수행중인 디렉터리의 파일 목록을 파일로 만드는 함수 구현되어있음

#include <errno.h>

//macro
#define SERV_IP "127.0.0.1" // 서버의 로컬 호스트 주소를 define
#define SERV_PORT 4140      //서버의 포트 번호를 define
#define BACKLOG 10
#define INIT_STATE 0
#define AFTER_STATE 1

void recv_file(void); //각 클라이언트로부터 파일을 recv 하는 로직 함수화 필요
int make_tmp_file(int token);
//lst 파일들이 있는 경로를 입력받고
//해당 경로에있는 모든 lst 파일을 순회하면서
//임시 파일에 끝에 계속해서 데이터를 붙인다
//이후 임시파일의 파일디스크립터를 리턴해 소모할 수 있도록 한다.

extern int errno;

int main()
{
    int sockfd, new_fd; //server 호스트의 소켓 파일디스크립터 및 새로운 연결을 정의할 new_fd
    int file_size;      //파일의 사이즈, 미사용중
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    unsigned int sin_size;
    char file_name[BUFSIZE];                           //파일의 이름 -> 서버에서 유저별로 관리하기 위함
    char server_file_path[BUFSIZE] = "./data/server_"; //각 유저별로 서버에 파일을 따로 저장함.
    //서버 코드가 돌아가는 디렉터리의 하위 폴더인 data 밑에 저장함

    //for server concurrency, we will fork server process with each connection request.
    pid_t childpid;
    int rcv_byte;
    char *buf = (char *)malloc(BUFSIZE);
    char *tmp_file_name = (char *)malloc(BUFSIZE);
    char id[20];
    char pw[20];
    char msg[512];

    int val = 1;
    int state = INIT_STATE;

    ssize_t ret, nr;

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
                    memset(buf, 0, BUFSIZE);
                    *(int *)&buf[0] = 1; //user1 인증 성공 정보를 보내기 위함(token)
                    send(new_fd, buf, sizeof(buf), 0);
                    //1이라는 정수를 전송해서 user1 로그인이 성공했음을 클라이언트에게 알림
                    //이제 파일을 전송받기위해 대기.
                    read(new_fd, file_name, BUFSIZE);
                    printf("client will sent this file %s \n", file_name);         //먼저 이 때 클라이언트가 파일 이름을 보내줄 것
                    strcat(server_file_path, file_name);                           //server_user1_file_list.lst 라는 이름으로 파일 관리.
                    int fd = 0;                                                    //fd를 열어놓음
                    fd = open(server_file_path, O_CREAT | O_RDWR | O_TRUNC, 0644); //읽기쓰기 및 덮어쓰기, 실행권한
                    //기존에 user의 파일이 있을경우 업데이트를 위해 항상 접속하면 새로 작성한다.
                    //파일 수신 로직
                    int n_bytes = 0;
                    while ((n_bytes = read(new_fd, buf, BUFSIZE)) > 0)
                    {
                        write(fd, buf, n_bytes);
                        printf("%s was receive\n n_bytes : %d ", buf, n_bytes);
                        if (n_bytes < BUFSIZE)
                        {
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
                    for (;;)
                    {
                        if (state == 1)
                        {
                            read(sockfd, buf, BUFSIZE);
                            printf("what the hell... %s", buf);
                        }
                        int rb = 0;
                        memset(buf, 0x00, BUFSIZE);
                        printf("server is wating for client's command.....\n");

                        if ((rb = (read(new_fd, buf, BUFSIZE))) == -1)
                        {
                            perror("read error ! "); //지금 connection reset by peer 발생함
                        }

                        printf("client send this command %s and length %d \n", buf, rb);

                        if (strcmp("exit", buf) == 0)
                        {
                            printf("client conenct close !\n");
                            strcpy(buf, "exit");
                            send(new_fd, buf, BUFSIZE, 0);
                            break;
                        }

                        else if (strcmp("show", buf) == 0)
                        {
                            int rd_bytes = 0;
                            printf("user%d requested file list ... \n", token);
                            if (make_tmp_file(token) != 1)
                            {
                                printf("error occured on server.");
                                send(new_fd, "exit", BUFSIZE, 0); //for exit client
                            }
                            strcpy(buf, "list"); //list 파일을 보내줄것이라고 이야기 해주기.
                            send(new_fd, buf, BUFSIZE, 0);
                            strcpy(tmp_file_name, "user1_tmp.lst");
                            fd = open(tmp_file_name, O_RDONLY);
                            // 서버와 클라이언트 간 byte stream 파일을 파일 크기를 미리 주고 받지 않더라도
                            // 전송, 수신을 올바르게 하는 방법을 찾아보자 ㅠ ㅠ
                            // while ((n_bytes = read(fd, buf, BUFSIZE)) > 0)
                            // {
                            //     if (n_bytes < BUFSIZE)
                            //     {
                            //         printf("inner : serve send %d bytes !! \n", n_bytes);
                            //         buf[n_bytes + 1] = '\0';
                            //         memset(&buf[n_bytes + 2], 0x00, BUFSIZE - n_bytes - 1);
                            //         send(new_fd, buf, BUFSIZE, 0);
                            //         //printf("*********** sended : %s", buf);
                            //         break;
                            //     }
                            //     printf("outer : server send %d bytes !! \n ", n_bytes);
                            //     //printf("outer of n bytes *** %s", buf);
                            //     send(new_fd, buf, BUFSIZE, 0);
                            // }
                            // int len = BUFSIZE;
                            // while(len != 0 && (ret = read(fd, buf, BUFSIZE)) != 0){
                            //     if (ret == -1){
                            //         if (errno == EINTR)
                            //             continue;
                            //         perror("write");
                            //         break;
                            //     }
                            //     len -= ret;
                            //     buf += ret;
                            //     send(new_fd, buf, ret, 0);
                            // }

                            printf("server send done !! \n");
                            state = 1;
                            close(fd);
                        }

                        else
                        {
                            printf("thre is no command like that ! : %s \n", buf);
                            strcpy(buf, "exit");
                            send(new_fd, buf, BUFSIZE, 0);
                            break;
                        }
                    }
                    close(new_fd);
                    break;
                }
                else if (token == USER2_LOGIN)
                {
                    memset(buf, 0, BUFSIZE);
                    *(int *)&buf[0] = token; //user2 인증 성공 정보를 보내기 위함
                    send(new_fd, buf, sizeof(buf), 0);
                    read(new_fd, file_name, BUFSIZE);
                    printf("client will sent this file %s \n", file_name);
                    strcat(server_file_path, file_name);
                    int fd = 0;
                    fd = open(server_file_path, O_CREAT | O_RDWR | O_TRUNC, 0644); //읽기쓰기 및 덮어쓰기, 실행권한
                    int n_bytes = 0;
                    while ((n_bytes = read(new_fd, buf, BUFSIZE)) > 0)
                    {
                        write(fd, buf, n_bytes);
                        printf("%s was receive\n n_bytes : %d ", buf, n_bytes);
                    }
                    printf("file receive done. \n");
                    memset(buf, 0, BUFSIZE); // buffer reset !
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

int make_tmp_file(int token)
{
    int n_bytes;
    int tmp_fd; //순회하면서 돌 fd
    int fd;
    char user_token[10];
    char buf[BUFSIZE]; //유용하게 사용할 버퍼
    char *path = (char *)malloc(BUFSIZE);
    char *tmp_file_name = (char *)malloc(BUFSIZE);
    DIR *dir = NULL;
    struct dirent *entry = NULL; //디럭터리에서 파일만 찾을려고 함
    struct stat info;            //파일의 속성을 파악하기 위한 구조체

    sprintf(user_token, "%d", token); //int형 user token을 문자열로 변환
    strcpy(buf, "user");              //user
    strcat(buf, user_token);          //user1
    strcat(buf, "_tmp.lst");          //user1_tmp.lst
    strcpy(tmp_file_name, buf);       //tmp_file_name에 user1_tmp.lst 문자열 저장
    //tmp_file_name == "user1_tmp.lst"
    getcwd(buf, BUFSIZE); //서버코드가 실행중인 경로를 얻음.
    // /Users/gimsehwan/Desktop/ingkle/studying_C/2020_fall_embeded_os/assignmnet_2
    strcat(buf, "/data"); // 하위 디렉터리 /data 의 절대경로를 얻음
    // buf == "/Users/gimsehwan/Desktop/ingkle/studying_C/2020_fall_embeded_os/assignmnet_2/data"
    // strcat(buf, tmp_file_name);
    strcpy(path, buf); //path에 buf에 담긴 경로 문자열 담아놓음
    strcat(path, "/");
    strcat(path, tmp_file_name);
    fd = open(path,
              O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open error");
        return -1;
    }
    //다시 ./data 경로를 지정하기 위해서 문자열 처리
    getcwd(buf, BUFSIZE); //서버코드가 실행중인 경로를 얻음.
    strcat(buf, "/data"); // 하위 디렉터리 /data 의 절대경로를 얻음
    // strcat(buf, tmp_file_name);
    strcpy(path, buf); //path에 buf에 담긴 경로 문자열 담아놓음
    // /Users/gimsehwan/Desktop/ingkle/studying_C/2020_fall_embeded_os/assignmnet_2/data
    if ((dir = opendir(path)) == NULL)
    {
        printf("open dir error \n");
    }

    chdir(path);
    while ((entry = readdir(dir)) != NULL)
    {
        lstat(entry->d_name, &info);
        if (S_ISREG(info.st_mode))
        {
            if ((tmp_fd = open(entry->d_name, O_RDWR)) < 0)
            {
                perror("open error");
            }
            if ((strcmp(entry->d_name, tmp_file_name)) == 0)
            {
                continue; //임시파일 자체 이름은 패스
            }
            //임시 파일을 생성한다.
            while ((n_bytes = read(tmp_fd, buf, BUFSIZE)) > 0)
            {
                if (n_bytes < BUFSIZE)
                {
                    buf[n_bytes] = '\0';
                    write(fd, buf, n_bytes);
                    break;
                }
                write(fd, buf, BUFSIZE);
            }
            //각 파일의 맨 앞에 인덱스를 붙여주는 로직
            close(tmp_fd);
        }
    }
    free(path);
    free(tmp_file_name);
    closedir(dir);
    close(fd);
    return 1;
}