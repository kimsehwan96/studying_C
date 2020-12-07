#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

#define BUF_SIZE 1024
#define SERV_IP "127.0.0.1"
#define PORT 4140
int main(void) {
    int sock;
    char buf[BUF_SIZE];
    int str_len;
    struct sockaddr_in serv_adr;

    FILE *readfp;
    FILE *writefp;

    int file_fd;
    FILE * fp;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1)
        perror("socket");
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(SERV_IP);
    serv_adr.sin_port=htons(PORT);

    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        perror("connect");
    
    readfp = fdopen(sock, "r"); //입력버퍼
    writefp = fdopen(sock, "w"); // 출력 버퍼

    // while(true){
    //     fputs("Input message (Q to exit): ", stdout);
    //     fgets(buf, BUF_SIZE, stdin);

    //     if(!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
    //         break;
    //     if(!strcmp(buf, "file"))
    //         break; 
    //     fputs(buf, writefp); // 널 문자를 제외하고 전송함
    //     fflush(writefp); //입출력 버퍼의 출력 버퍼에서 소켓 출력 버퍼로 이동시킴

    //     fgets(buf, BUF_SIZE, readfp); //함수 특성상 널 문자를 마지막에 자동 추가
    //     printf("Message from serv : %s ", buf);
    // }
    //파일 디스크립터로 파일을 읽기쓰기 전용으로 하나 열음
    file_fd = open("test.file", O_RDWR);
    //파일 디스크립터를 파일포인터로 바꾼당.

    /* 파일을 서버로 끝까지 보내는 로직 -> 예를 써서 텀플 구현 해야 할듯 */
    fp = fdopen(file_fd, "r+");
    while(!feof(fp)){ //eof일때까지 쭉 쭉 보냄.
        fgets(buf, BUF_SIZE, fp);
        fputs(buf, writefp);
        fflush(writefp);
    }
    printf("file send done. \n");
    fclose(readfp);
    fclose(writefp);
    fclose(fp);
    return 0;
}