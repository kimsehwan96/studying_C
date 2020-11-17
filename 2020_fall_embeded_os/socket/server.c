#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 4000
#define BACKLOG 10
#define INIT_MSG "===================\n Hi this is p2p test plz login\n ===============\n"
#define ID_REQ "input id : "
#define PW_REQ "input password : "
#define USER1_ID "user"
#define USER1_PW "passwd1"
#define USER2_ID "user2"
#define USER2_PW "passwd2"
#define USER1_LOGIN 1
#define USER2_LOGIN 2
#define LOGIN_FAIL 0

int authenticate(char *id, char *pw)
{
    if (strcmp(id, USER1_ID) == 0)
    {
        if (strcmp(pw, USER1_PW) == 0)
        {
            return USER1_LOGIN;
        }
    }
    else if (strcmp(id, USER2_ID) == 0)
    {
        if (strcmp(pw, USER2_PW) == 0)
        {
            return USER2_LOGIN;
        }
    }
    else
        return LOGIN_FAIL;
}

int main(void)
{
    int sockfd, new_fd;

    struct sockaddr_in my_addr;

    struct sockaddr_in their_addr;

    unsigned int sin_size;

    int rcv_byte;
    char buf[512];

    char id[20];
    char pw[20];

    char msg[512];

    int val = 1;

    pid_t pid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //TCP
    if (sockfd == -1)
    {
        perror("server-socker() error");
        exit(1);
    }
    else
        printf("server socket() sockfd is ok \n");

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

    //init buffer status
    memset(id, 0, sizeof(id));
    memset(pw, 0, sizeof(pw));

    sin_size = sizeof(struct sockaddr_in);

    for (;;)
    {
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd != -1)
        {
            printf("auccept() is ok\n");
            send(new_fd, ID_REQ, strlen(ID_REQ) + 1, 0);
            read(new_fd, id, sizeof(id));
            send(new_fd, PW_REQ, strlen(PW_REQ) + 1, 0);
            read(new_fd, pw, sizeof(pw));
            printf("===========================\n");
            printf("User Information\n");
            printf("id : %s  pw : %s \n", id, pw);
            printf("===========================\n");
            if (authenticate(id, pw) == USER1_LOGIN)
            {
                printf("USER1 Login Success \n");
                send(new_fd, "Login Success User1 ! \n", 512, 0);
                close(new_fd);
            }
            else if (authenticate(id, pw) == USER2_LOGIN)
            {
                printf("USER2 Login Success\n");
                send(new_fd, "Login Success User2 ! \n", 512, 0);
                close(new_fd);
            }
            else
            {
                printf("there is no such that user %s\n", id);
                send(new_fd, "Login Fail \n", 512, 0);
                close(new_fd);
            }
        }
        else {
            printf("accept fail !");
            exit(0);
        }
    }
    // new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size) == -1;
    // if (new_fd == -1){
    //     printf("accpet error");
    // }
    // else {
    //     printf("accept is ok\n");
    //     send(new_fd, INIT_MSG, strlen(INIT_MSG) +1, 0);//client에게 init 메시지 전송.
    // }
    // recv(new_fd, buf, sizeof(buf), 0);

    close(new_fd);
    close(sockfd);

    return 0;
}
