#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

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

//입력 스트림으로부터 받은 데이터를 출력 스트림으로 다 꽂아주는 로직
void recv_file(FILE *readstream, FILE *writestream) {
    int recv_size;
    int recv_file_fd;
    char buf[1024]; //버퍼 사이즈는 널널하게 1024바이트
    while(!feof(readstream)){
        fgets(buf, 1024, readstream); //파일을 다 받고나서 사이즈를 리턴해주기
        fputs(buf, writestream);
    }
}

int main(void) {
    FILE *readfp;
    FILE *writefp;
    int result = 0;
    int fd;
    int target_fd;
    int n_bytes;
    char buf[512];
    
    readfp = fopen("test.file", "r");
    
    
    writefp = fopen("result.txt", "w+");
    result = recv_file(readfp, writefp);

    printf("recv file size %d", result);
    return 0;
}