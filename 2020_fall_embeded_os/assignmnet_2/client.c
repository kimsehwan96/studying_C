#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "common.h"
#include "list_func.h" //내부 파일 리스트를 생성하는 함수
#include "my_ip.h"     //ip check 함수

#define SERV_IP "127.0.0.1"
#define SERV_PORT 4140

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

void send_file(void); //각 클라이언트 별로 파일을 send하는 로직 함수화 필요.

int main(void)
{
    int sockfd, fd;
    struct sockaddr_in dest_addr;
    int rcv_byte;
    char *buf = (char *)malloc(BUFSIZE);
    char *file_buf = (char *)malloc(BUFSIZE);
    char id[20];
    char pw[20];
    char file_name[512];
    int file_size;

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
    if (*(int *)&buf[0] == 1)
    { //유저 1 로그인 성공
        printf("login success\n");
        //login success logic here
        mklistf("user1", "127.0.0.1"); //뒤에 인자(ip address)는 my_ip 헤더를 이용할 것.
        //user1_file_list.lst 생성 완료, 이 파일을 서버에 전송해야 함.
        //1. 파일 이름을 먼저 전송한다
        //2. EOF까지 파일을 char로 BUFSIZE에 최대한 담아서 보낸다.

        //file descriptor open
        strcpy(file_name, "user1_file_list.lst");
        //filename send
        if ((fd = open("user1_file_list.lst", O_RDWR)) < 0)
        {
            perror("open() error !");
        }
        //file name sending
        send(sockfd, file_name, sizeof(file_name), 0);
        //send file!
        int n_bytes = 0;
        int count = 0;
        /*
            n_bytes는 read 성공시 읽은 바이트 수 반환
            만약 BUFSIZE -> 512 만큼 읽기를 요청했는데
            BUFSIZE보다 적은 값이 return ->EOF가 마지막에 포함되었다는 뜻
            따라서, n_bytes만큼 데이터를 송신해야 하며
            buf[n_bytes]의 EOF문자를 NULL로 바꿔주는 로직이 포함 됨.
        */
        while ((n_bytes = read(fd, file_buf, BUFSIZE)) > 0)
        {
            if (n_bytes < BUFSIZE)
            {
                buf[n_bytes] = '\0';
            }
            count++;
            printf("count : %d n_bytes : %d : this is sended : %s ", count, n_bytes, file_buf);
            send(sockfd, file_buf, n_bytes, 0);
        }

        printf("file send done ! \n");
        free(file_buf);
        close(fd);
    }
    else if (*(int *)&buf[0] == 1)
    {
        //user 2 logic
    }
    else
    {
        printf("login failed.");
    }
    close(sockfd);
    free(buf);

    return 0;
}