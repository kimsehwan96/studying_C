# include <stdio.h>

int main (void)
{

    int num = 100;
    printf("num = %d\n", num);  // 정수형 포메팅 문자는 %d
    double num_2 = 12.3;
    printf("num_2 = %f\n", num_2); // 플로팅 은 %f
    char ch = 'a';
    printf("ch = %c \t", ch);
    printf("ch = %d 포메팅 문자를 %d로 했기 때문에 아스키코드의 정수값인 97이 나온다. \t", ch);
    printf("ch = %c 포메팅 문자를 캐릭터형으로 했지만. 어쨌든 아스키코드의 값에 1을 더한 아스키코드 값 98에 해당하는 b가 출력된다. \t", ch+1);
    printf("ch = %d \t", ch+1);

    return 0;
}