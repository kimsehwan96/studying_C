# include <stdio.h>
# include <limits.h>


int main ()
{
    char num1 = CHAR_MIN - 1; // char의 min 값보다 1 낮게 할당
    short num2 = SHRT_MIN - 1; // shrot 의 min 값보다 1 낮게 할당
    int num3 = INT_MIN - 1; // int 의 mmin 값보다 1 낮게 할당
    long long num4 = LLONG_MIN - 1; // long long 의 min 값보다 1 낮게 할당

    printf("%d %d %d %lld \n", num1, num2, num3, num4);

    unsigned char num5 = 0 - 1; // unsigned 최솟값 값보다 1 낮게 할당
    unsigned short num6 = 0 - 1;
    unsigned int num7 = 0 - 1;
    unsigned long long num8 = 0 - 1;

    printf("%u %u %u %llu", num5, num6, num7, num8);

/*
    정수형 데이터에서 최솟값보다 낮게 언더플로우되면 다시 최댓값부터 시작한다.
*/
    
}