#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "benchmarks.h"


#define MSG_SIZE 80
#define PIPENAME "./named_pipe_file"

int main(void) {
  char msg[MSG_SIZE];
  int fd;
  int nread, rc;
  double startTime, endTime, benchmark = 0;

  /* 기존에 named pipe가 있으면 삭제 */
  if (access(PIPENAME,F_OK) == 0) {
    unlink(PIPENAME);
  }

  /* named pipe 생성하기 */
  if ((rc = mkfifo(PIPENAME,0666)) < 0) {
    printf("fail to make named pipe\n");
    return 0;
  }

  /* named pipe 열기, Read Write가능 해야 한다 */
  if ((fd = open(PIPENAME, O_RDWR)) < 0) {
    printf("fail to open named pipe\n");
    return 0;
  }
  
  startTime = (float)clock()/CLOCKS_PER_SEC; //start to benchmark
  while (1) {
    if ((nread = read(fd, msg, sizeof(msg))) < 0 ) {
      printf("fail to call read()\n");
      return 0;
    }
    //printf("recv: %s\n", msg);
    if (strcmp(msg, "exit") == 0) {
        endTime = (float)clock()/CLOCKS_PER_SEC;
        benchmark = endTime - startTime;
        printf("total processed time %.3lf 초\n", benchmark);
        return 0;
    }
  }
  return 0;
}
