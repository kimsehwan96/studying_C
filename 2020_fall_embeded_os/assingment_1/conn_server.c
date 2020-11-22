#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_IP "220.149.128.100" // 서버의 로컬 호스트 주소를 define
#define SERV_PORT 4140 //서버의 포트 번호를 define
#define BACKLOG 10
// 사용자에게 전달할 메시지 정의
#define INIT_MSG "===================\n Hi this is p2p test plz login\n ===============\n"
#define ID_REQ "input id : "
#define PW_REQ "input password : "
#define USER1_ID "user"
#define USER1_PW "passwd1"
#define USER2_ID "user2"
#define USER2_PW "passwd2"
// 유저 인증 함수에서 사용할 Magic Number 정의.
#define USER1_LOGIN 1
#define USER2_LOGIN 2
#define LOGIN_FAIL 0

// 유저의 인증로직을 위한 함수.
unsigned int authenticate(char *id, char *pw)
{
    if (strcmp(id, USER1_ID) == 0)
    {
        if (strcmp(pw, USER1_PW) == 0)
        {
            return USER1_LOGIN;
        }
        else
        {
            return LOGIN_FAIL;
        }
    }
    else if (strcmp(id, USER2_ID) == 0)
    {
        if (strcmp(pw, USER2_PW) == 0)
        {
            return USER2_LOGIN;
        }
        else
        {
            return LOGIN_FAIL;
        }
    }
    else
        return LOGIN_FAIL;
}
// 유저의 id와 passwd를 인자로 받아, 사전 정의된 유저 정보에 대해서만 처리
// 더 좋은 방법이 있을 것 같지만 이번 과제에서는 이렇게 처리할 예정,

int main(void)
{
    int sockfd, new_fd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    unsigned int sin_size;
    //fork이후 pid 체크를 위해서,
    pid_t childpid;
    int rcv_byte;
    //입출력 처리를 할 문자열 버퍼들
    char buf[512];
    char id[20];
    char pw[20];
    char msg[512];

    int val = 1;


    sockfd = socket(AF_INET, SOCK_STREAM, 0); //TCP
    if (sockfd == -1)
    {
        perror("server-socker() error");
        exit(1);
    }
    else
        printf("server socket() sockfd is ok \n");

    //address family로 AF_INET 정의.
    my_addr.sin_family = AF_INET;

    my_addr.sin_port = htons(SERV_PORT);

    my_addr.sin_addr.s_addr = INADDR_ANY;

    memset(&(my_addr.sin_zero), 0, 8);

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&val, sizeof(val)) < 0)
    {
        perror("setsockopt");
        close(sockfd);
        return -1;
    }

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == 1)
    {
        perror("bind err ");
        exit(1);
    }
    else
        printf("server bind ok \n");

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("linsten error");
        exit(1);
    }
    else
    {
        printf("listen ok\n\n");
    }

    //버퍼를 모두 0으로 초기화.
    memset(id, 0, sizeof(id));
    memset(pw, 0, sizeof(pw));

    sin_size = sizeof(struct sockaddr_in);

    // 메인 루프, 인터럽트, return, break; 발생 전까지 무한루프.
    for (;;)
    {
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd < 0)
        {
            exit(1);
        }
        printf("Connection accepted from %s\n", inet_ntoa(their_addr.sin_addr));

        if ((childpid = fork()) == 0)
        {
            close(sockfd);
            for (;;)
            {
                //accept 이후 로직.
                printf("auccept() is ok\n");
                send(new_fd, ID_REQ, strlen(ID_REQ) + 1, 0);
                read(new_fd, id, sizeof(id));
                send(new_fd, PW_REQ, strlen(PW_REQ) + 1, 0);
                read(new_fd, pw, sizeof(pw));
                //id를 서버에서 요청 후 저장, pw도 요청 후 저장

                //유저가 입력한 내용을 서버에서 출력
                printf("===========================\n");
                printf("User Information\n");
                printf("id : %s  pw : %s \n", id, pw);
                printf("===========================\n");

                // 인증 로직을 실행, 좋은 코드는 아닌 것 같습니다.
                if (authenticate(id, pw) == USER1_LOGIN)
                {
                    printf("%s Login Success \n", id);
                    send(new_fd, "Login Success User1 ! \n", 512, 0);
                    printf("Disconnected from %s\n", inet_ntoa(their_addr.sin_addr));
                    close(new_fd);
                    break;
                }
                else if (authenticate(id, pw) == USER2_LOGIN)
                {
                    printf("%s Login Success\n", id);
                    send(new_fd, "Login Success User2 ! \n", 512, 0);
                    printf("Disconnected from %s\n", inet_ntoa(their_addr.sin_addr));
                    close(new_fd);
                    break;
                }
                else
                {
                    printf("there is no such that infotmation id : %s pw : %s\n", id, pw);
                    send(new_fd, "Login Fail \n", 512, 0);
                    printf("Disconnected from %s\n", inet_ntoa(their_addr.sin_addr));
                    close(new_fd);
                    break;
                }
            }
        }
    }
    //sockfd와 새로운 소켓 연결을 정의하던 new_fd 모두 close.
    close(new_fd);
    close(sockfd);

    return 0;
}