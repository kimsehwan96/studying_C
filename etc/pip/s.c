#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<string.h>
#define MAX_SIZE 50

int data_num;
char *fifo="fifo";

int calculation_Checksum(int* message){
        int Checksum;
        int sum = 0, pre_sum = 0;

        for(int n = 0; n < data_num; n++){
                sum += message[n];
                if(pre_sum > sum)
                        sum++;
                pre_sum = sum;
        }

        Checksum = ~sum;

        message[data_num] = Checksum;
        data_num++;

        return Checksum;
}

void parsing(char buf[], int mes[]){
        data_num = 0;
        int i = 0;
        int count = 0;
        char temp[MAX_SIZE+1];
        temp[0] = ' ';
        // 맨 앞에 데이터 개수때문에 count-1
        while(data_num!= count-1){
                if(buf[i]=='/'){
                    // 4/1/2/3/4 -> 
                        //데이터 개수먼저 저장
                        if(count==0){
                                data_num = atoi(temp);
                        }
                        else{
                                mes[count-1] = atoi(temp);
                        }
                        temp[0] = ' ';
                        count++;
                }
                else{
                        if(temp[0] == ' '){
                                strcpy(temp, &buf[i]);
                        }
                        else{
                                strcat(temp, &buf[i]);
                        }

                }
                i++;
        }
}

int main(void){
        int mes[MAX_SIZE+1];
        memset(mes, 0, sizeof(mes));
        int value, fp;
        char buf[MAX_SIZE+1];


        // fifo 파일을 생성한다.
        if(mkfifo(fifo, 0666) != 0)
        {
                printf("create fifo failed\n");
                return -1;
        }

        // fifo 파일을 생성한다. O_RDONLY 는 읽기 전용.
        if((fp=open(fifo, O_RDONLY)) < 0)
        {
                printf("open fifo failed\n");
                return -1;
        }

        // 전송받은 내용은 buf에 저장된다.
        if( (value = read (fp, buf, MAX_SIZE)) > 0)
        {
                printf("new fifo message arrived : %s\n", buf);
        }

        parsing(buf, mes);

        // 왜 앞에 0이..
        for(int i=0;i<data_num+1;i++){
                printf("%d\n", mes[i]);
        }
        //int Cks = calculation_Checksum(mes);
        //printf("체크섬: %d", Cks);
        return 0;
}