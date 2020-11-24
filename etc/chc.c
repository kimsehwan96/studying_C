#include <stdio.h>
#define MAXNUM 100
 
int data_num;
 
void sending_message(int* message)
{
    printf("데이터의 갯수를 입력하시오.");
    scanf("%d", &data_num);
    if (data_num >= MAXNUM)
    {
        printf(" 최대 가능한 데이터 갯수를 초과하였습니다.\n 프로그램 종료.\n");
    }
 
 
    printf("데이터를 입력하시오.\n");
    for (int i = 0; i < data_num; i++)
    {
        scanf("%d", &message[i]);
    }
    printf("데이터 입력이 끝났습니다.\n\n");
 
}
 
int calculaton_Checksum(int* message)
{
    /* 임의의 길이를 갖는 메시지를 넘겨받아 Checksum을 계산하여 return한다.*/
    int Checksum;
    int sum = 0, pre_sum = 0;
 
    for (int n = 0; n < data_num; n++)
    {
        sum += message[n];
        if (pre_sum > sum)
            sum++;
        pre_sum = sum;
    }
 
    Checksum = ~sum;
 
    message[data_num] = Checksum;
    data_num++;
 
    return Checksum;
}
 
int check_Checksum(int* message)
{
    /* Checksum이 부착된 임의의 메시지를 넘겨받아, 에러가 검출되면 0, 아니면 1을 return한다. */
    int result = 0;
    int sum = 0, pre_sum = 0;
 
    for (int n = 0; n < data_num; n++)
    {
        sum += message[n];
        if ((unsigned int)pre_sum >(unsigned int)sum)
            sum++;
        pre_sum = (int)sum;
    }
 
    result = ~sum;
 
    if (result == 0)
        return 1;
    else
        return 0;
}
 
void print(int* message)
{
    printf("message: ");
 
    for (int i = 0; i < data_num; i++)
        printf("%d ", message[i]);
    printf("\n");
}
 
int main(void)
{
    int mes[MAXNUM];
    int Cks;
 
    sending_message(mes);
    printf("sender: \n");
    print(mes);
 
    Cks = calculaton_Checksum(mes);
    printf("checksum: %d\n\n", Cks);
 
    if (!check_Checksum(mes))
        printf("Checksum error!!");
    else{
        printf("Receiver: \n");
        print(mes);
    }
    return 0;
}
