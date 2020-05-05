# include <stdio.h>
# include <limits.h>


int main ()
{
    char num1 = CHAR_MAX + 1; // char의 max값보다 1넘게 할당
    short num2 = SHRT_MAX + 1; // shrot 의 max값보다 1 넘게 할당
    int num3 = INT_MAX + 1; // int 의 max 값보다 1 넘게 할당
    long long num4 = LLONG_MAX + 1; // long long 의 max 값보다 1 넘게 할당

    printf("%d %d %d %lld \n", num1, num2, num3, num4);

    unsigned char num5 = UCHAR_MAX + 1; // unsigned char 보다 1 넘게 할당
    unsigned short num6 = USHRT_MAX + 1;
    unsigned int num7 = UINT_MAX + 1;
    unsigned long long num8 = ULLONG_MAX + 1;

    printf("%u %u %u %llu", num5, num6, num7, num8);

/*
부호있는 정수형 데이터에서 최댓값을 넘게 overflow 발생하면 최소 음수값으로 표현되고
부호 없는 정수형 데이터에서 최댓값을 넘게 overflow 발생하면 0으로 표현된다.
*/
    
}