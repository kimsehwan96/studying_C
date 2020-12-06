/*
파일명 : read_file_size.c
컴파일 및 실행 : gcc -c read_file_size.c && gcc -o read_file_size read_file_size.o && ./read_file_size
lseek()을 이용하여 파일의 끝과 처음으로 이동하며 파일의 크기를 체크한다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

extern int errno;

int main(void){
    int fd, pos;

    fd = open("test.file", O_RDONLY);
    if (fd == -1){
        perror("open");
    }
    pos = lseek(fd, 0, SEEK_END); //파일의 끝으로 이동하고 그 오프셋을 반환받아 pos에 저장
    if (pos == (off_t) -1)
        perror("seek");
    lseek(fd, 0, SEEK_SET); //원래 파일 오프셋으로 이동
    printf("%s's file size is : %d", "test.file",pos); // pos 결과값 857 , 실제 파일 사이즈 857바이트. (이걸 이용하면 사이즈 체크후 소켓에서 처리하기 편할거같은뎅)
    close(fd);
    return 0;
}