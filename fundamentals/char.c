#include <stdio.h>

int main ()
{
    char c1 = 'a';
    char c2 = 'b';

    printf("%c %c \n", c1,c2);
    printf("%d %d\n",c1,c2);

    


char b1 = 0x61;
char b2 = 0x62;

printf("%d %d \n", b1,b2);
printf("%c %c\n",b1,b2);
printf( "0x%x 0x%x",b1,b2);

// 16진수 표현은 0x%x 로 표현을 하면 좋겠다
return 0;


}