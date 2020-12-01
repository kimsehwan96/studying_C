//here will be useful common functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
#define REQUEST_LIST_MSG "request list"
#define BUFSIZE 512

// 유저의 인증로직을 위한 함수.
unsigned int authenticate(int fd, char *id, char *pw)
{
    send(fd, ID_REQ, strlen(ID_REQ) + 1, 0); //strlen((char *)some_string +1) 인 이유는 Null 포함
    read(fd, id, sizeof(id));
    send(fd, PW_REQ, strlen(PW_REQ) + 1, 0);
    read(fd, pw, sizeof(pw));

    printf("===========================\n");
    printf("User Information\n");
    printf("id : %s  pw : %s \n", id, pw);
    printf("===========================\n");

    if (strcmp(id, USER1_ID) == 0)
    {
        if (strcmp(pw, USER1_PW) == 0)
        {
            printf("%s Login success \n", id);
            //send(fd, "LOGIN SUCCESS USER 1 \n", 512, 0);
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
            printf("%s Login success \n", id);
            //send(fd, "LOGIN SUCCESS USER 2 \n", 512, 0);
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

//클라이언트는 서버에게 lst 파일을 보내줘야 함.
unsigned int client_process();
// 유저의 id와 passwd를 인자로 받아, 사전 정의된 유저 정보에 대해서만 처리
// 더 좋은 방법이 있을 것 같지만 이번 과제에서는 이렇게 처리할 예정,
