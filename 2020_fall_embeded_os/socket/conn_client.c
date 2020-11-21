#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 4140

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in dest_addr;
    int rcv_byte;
    char buf[512];
    char id[20];
    char pw[20];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("client-socker() error");
        exit(1);
    }
    else
        printf("client socket() sockfd is ok \n");

    dest_addr.sin_family = AF_INET;

    dest_addr.sin_port = htons(SERV_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(SERV_IP);

    memset(&(dest_addr.sin_zero), 0, 8);

    if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("client connect error");
        exit(1);
    }
    else
        printf("clinet connect is ok \n\n");

    read(sockfd, buf, sizeof(buf));
    printf("%s", buf);
    scanf("%s", id);
    send(sockfd, id, strlen(id) + 1, 0);
    memset(buf, 0, sizeof(buf));
    read(sockfd, buf, sizeof(buf));
    printf("\n%s", buf);
    scanf("%s", pw);
    send(sockfd, pw, strlen(pw) + 1, 0);
    memset(buf, 0, sizeof(buf));
    read(sockfd, buf, sizeof(buf));
    printf("\n%s", buf);

    close(sockfd);

    return 0;
}
