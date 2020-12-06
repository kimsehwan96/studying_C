#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define TIMEOUT 5 /* 타임아웃 (초) */
#define BUF_LEN 1024 /* 읽기 버퍼 사이즈 (바이트) */

int main(void) {
    struct timeval tv;
    fd_set readfds;
    int ret;

    /* */
}