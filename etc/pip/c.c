#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


char *fifo="fifo";
int main(){
        int fp; // fifo 파일 포인터
        char data;
        char datas[50];
        //int line[255];
        int count=0;

        FILE *fd = fopen("data.txt","r");
        if(fd == NULL){
                printf("file open error\n");
                exit(1);
        }


        if((fp = open(fifo, O_WRONLY)) < 0){
                printf("fifo file open error\n");
                return -1;
        }


        int i=2;
        while(1){
                data=fgetc(fd);
                fgetc(fd);
                if(feof(fd))
                        break;
                printf("%c\n",data);
                datas[i]=data;
                datas[i+1]='/';
                count++;
                i=i+2;
        }
        datas[i] = 'E';
        printf("데이터의 수 : %d\n",count);
        datas[0]=count+48; // ascii 변환
        datas[1]='/';

        // 파일에 쓰면 끝!
        write(fp, datas, sizeof(datas));

        close(fp);
        fclose(fd);
        return 0;
}