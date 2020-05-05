# include <stdio.h>
# include <limits.h>

int main ()
{
    char num1 = CHAR_MIN;
    short num_2 = SHRT_MIN;
    int num_3 = INT_MIN;
    long num_4 = LONG_MIN;
    long long num_5 = LLONG_MIN;

    printf("%d %d %d %ld %lld \n",num1,num_2,num_3,num_4, num_5);

    return 0;
    
}