#include <string.h>
#include <stdio.h>
#include <stdlib.h> 

#define MAX_SIZE 50

int data_num = 0;

void parsing(char buf[], int mes[]){
        int i = 0;
        int count = 0;
        char temp[MAX_SIZE+1];
        temp[0] = ' ';
        // 맨 앞에 데이터 개수때문에 count-1
        while(data_num != count-1){
                if(buf[i]=='/'){
                        //데이터 개수먼저 저장
                        if(count==0){
                                data_num = atoi(temp);
                        }
                        else{
                                mes[count] = atoi(temp);
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

int main () {
    int mes[MAX_SIZE+1];
    char a[50] = "3/21/5/4";
    memset(mes, 0, 51);

    parsing(a, mes);
    for (int i = 0; i<51; i++){
        printf("%d\n",mes[i]);
    }


}