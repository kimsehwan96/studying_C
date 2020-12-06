/*
파일명 : all_data_read.c
컴파일 및 실행 : gcc -c all_data_read.c && gcc -o all_data_read all_data_read.o && ./all_data_read
내용 : 파일을 열고, 파일의 전체 바이트를 읽는 함수이다.
len 바이트만큼 모두 읽기를 시도하고, len 만큼 읽기 전에 EOF를 만나면 종료되는 코드 조각이다.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

extern int errno;

int main(void){
    int fd, len;
    char *buf = (char *)malloc(512);
    ssize_t ret;

    len = 65536; //그냥 긴 값 테스트
    fd = open("test.file", O_RDONLY);
    if (fd == -1){
        perror("open");
    }
    while(len != 0 && (ret = read(fd, buf, len)) != 0) {
        printf("%s", buf);
        if (ret == -1){
            if(errno == EINTR)
                continue; //한번 더 실행
            perror("read"); //다른 에러에 대해서는 break
            break;
        }
        len -= ret; //길이에서 ret된 값 만큼 뺀다.
        buf += ret; //버퍼의 포인터 연산(증가)시킨다.
    }
    printf("\nread done : left len : %d\n", len);

    close(fd);
    free(buf);
    return 0;
}