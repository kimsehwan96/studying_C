### read / write in socket 연구

```c
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
#define SIZE 1024

char* file1 = "recv.file";

void write_file(int sockfd, char* fn){
  int n;
  FILE *fp;
  char buffer[SIZE];

  fp = fopen(fn, "w+");
  while (1) {
    n = read(sockfd, buffer, SIZE);
    printf("this is n : %d \n", n);
    if (n <= 0){
      printf("this is n : %d \n", n);
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  fclose(fp);
  return;
}

int setup_socket(char *ip, int port); //return socket

int main(){
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;
  int sockfd;
  int new_sock;
  struct sockaddr_in new_addr;
  socklen_t addr_size;
  char buffer[SIZE];

 sockfd = setup_socket(ip, port);

  if(listen(sockfd, 10) == 0){
 printf("[+]Listening....\n");
 }else{
 perror("[-]Error in listening");
    exit(1);
 }

  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  write_file(new_sock, file1);
  printf("[+]Data written in the file successfully.\n");

  return 0;
}


int setup_socket(char *ip, int port){
  int e;
  int sockfd;
  struct sockaddr_in server_addr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0 ){
    perror("socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if(e<0){
    perror("bind");
    exit(1);
  }
   printf("[+]Binding successfull.\n");

   return sockfd;

}
```


```c
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
#define SIZE 1024

void send_file(FILE *fp, int sockfd){
  int n;
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

int main(){
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;

  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
  FILE *fp2;
  char *filename = "test.file";

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
 printf("[+]Connected to Server.\n");

  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
  }

  send_file(fp, sockfd);
  printf("[+]File data sent successfully.\n");

  close(sockfd);

  return 0;
}
```


- 서버사이드 출력

```console
(base)  ~/Desktop/ingkle/studying_C/시스템프로그래밍/examples/ftp   master ●  ./server 
[+]Server socket created successfully.
[+]Binding successfull.
[+]Listening....
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 1024 
this is n : 0 
this is n : 0 
[+]Data written in the file successfully.
```

- 정상적으로 eof (read 의 리턴 0 이 나옴.)


- EOF를 전달하기 가장 손쉬운 방법은.. socket close 인듯...
