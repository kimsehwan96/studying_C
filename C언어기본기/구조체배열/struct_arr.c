#include <stdio.h>

struct Point2d{
    int x;
    int y;
};

int main(void){
    struct Point2d p[3]; //크기가 3인 배열 선언
    p[0].x = 10;    // 인덱스로 요소에 접근한 뒤 점으로 멤버에 접근
    p[0].y = 20;
    p[1].x = 30;
    p[1].y = 40;
    p[2].x = 50;
    p[2].y = 60;

    printf("%d %d\n", p[0].x, p[0].y);    // 10 20
    printf("%d %d\n", p[1].x, p[1].y);    // 30 40
    printf("%d %d\n", p[2].x, p[2].y);    // 50 60

    return 0
}