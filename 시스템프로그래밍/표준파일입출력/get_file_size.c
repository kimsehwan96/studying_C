#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int get_file_size(FILE *stream) {
    int fd, pos;
    if((fd = fileno(stream)) < 0){
        perror("fileno");
        return -1; //error intger return
    }
    //파일 오프셋을 0으로 설정
    lseek(fd, 0, SEEK_SET);
    //파일 오프셋을 파일의 끝으로 설정하고 크기 받아오기
    pos = lseek(fd, 0, SEEK_END);
    //다시 0으로
    lseek(fd, 0, SEEK_SET);
    return pos;
}

int main(void) {
    FILE *fp;
    int result = 0;
    
    fp = fopen("test.file", "r");
    result = get_file_size(fp);
    
    printf("file size : %d", result);
    return 0;
}