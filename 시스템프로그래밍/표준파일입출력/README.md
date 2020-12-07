# 표준 파일 입출력

- 저수준 인터페이스인 read, write 와는 다른 것.

- 파일 열기 : fopen()
- 파일 닫기 : fclose()

- 단점
    - 양방향 통신이 쉽지 않음
    - 상황에 따라서 fflush 함수의 호출이 빈번히 등장 할 수 있음


### fdopen 함수를 이용한 FILE 구조체 포인터로의 변환

```c
#include <stdio.h>

FILE * fdopen(int fildes, const char * mode);
// -> 성공시 변환된 FILE 구조체 포인터, 실패시 NULL 반환
```

### fileno 함수를 이용한 파일디스크립터로의 변환

```c
#include <stdio.h>

int fileno(FILE * stream);
// -> 성공시 변환된 파일 디스크립터, 실패시 -1 반환
```



### 클라이언트가 서버로 특정 파일을 EOF(파일의 끝)까지 보내는 로직

- 서버코드
```c
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
        fflush(fp); //출력 버퍼에 있는 데이터를 열어놓은 파일로 바로 밀어버림.
    }

    fclose(readfp);
    fclose(writefp);
    fclose(fp);
    close(serv_sock);
    return 0;
}
```


- 클라이언트 코드

```c
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
```

