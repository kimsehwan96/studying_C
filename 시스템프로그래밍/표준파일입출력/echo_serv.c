#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define SERV_IP "127.0.0.1"
#define PORT 4140


int main(void){
    int serv_sock, clnt_sock;
    char buf[BUF_SIZE];
    int str_len, i;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;
    FILE *readfp; // 입력 버퍼 스트림
    FILE *writefp; // 출력 버퍼 스트림 -> 표준 입출력을 이용해 소켓을 쓰면 이케 입출력 스트림 나눠야대

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        perror("serv_sock");
    }
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr= INADDR_ANY;
    serv_adr.sin_port=htons(PORT);

    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        perror("bind");
    if(listen(serv_sock, 5)==-1)
        perror("listen");

    clnt_adr_sz = sizeof(clnt_adr);

    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

    if (clnt_sock==-1)
        perror("accept");
    
    readfp = fdopen(clnt_sock, "r"); //입력 스트림 버퍼
    writefp = fdopen(clnt_sock, "w"); //출력 스트림 버퍼 이케 각 1세트
    /* 파일을 클라이언트로부터 끝까지 받는 로직 -> 예를 써서 텀플 구현 해야 할듯 */
    FILE *fp;
    fp = fopen("recv.file", "w+");
    while(!feof(readfp)){
        fgets(buf, BUF_SIZE, readfp);
        fputs(buf, fp);
        fflush(fp); //출력 버퍼에 있는 데이터를 소켓의 출력 버퍼로 즉시 내보냄
    }

    fclose(readfp);
    fclose(writefp);
    fclose(fp);
    close(serv_sock);
    return 0;
}