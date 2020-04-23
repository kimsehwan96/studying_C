#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>


/*파일 디스크립터란 ? 
 파일은 읽기, 쓰기, 혹은 읽기/쓰기 모드로 열 수 있다.
 이렇게 열린 파일은 그 파일에 대한 메타데이터와 연결된 고유한 디스크립터를 통해
 참조 할 수 있다. 리눅스 커널 내부에서 이 디스크립터는 정수(int)로 표현되며
 파일디스크립터라고 부른다. 파일 디스크립터는 사용자 영역에서 공유되며
 응용 프로그램이 파일에 접근 할 때 직접 사용한다. 시스템 프로그램응 대부분은
 이 파일 디스크립터를 열고 조작하고 닫는 작업이라고 할 수 있다.

*/
int main ()

{
    int fd1, fd2, sd1, sd2;

    fd1 = open("/etc/passwd", O_RDONLY, 0);
    printf("/etc/paswwd's file descriptor = %d \n ", fd1);

    sd1 = socket(PF_INET, SOCK_STREAM, 0);
    printf("strema socket descriptor = %d \n", sd1);

    sd2 = socket(PF_INET, SOCK_DGRAM, 0);

    printf("data gram's descriptor = %d \n ",sd2);

    fd2 = open("/etc/hosts",O_RDONLY, 0);
    printf("/etc/host's fd = %d \n", fd2);

    close(fd2);
    close(fd1);
    close(sd1);
    close(sd2);

    return 0;



}