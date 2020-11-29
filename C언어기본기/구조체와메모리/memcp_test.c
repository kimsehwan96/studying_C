#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Point2d {
    int x;
    int y;
};

int main(void){
    struct Point2d *p1 = (struct Point2d *)malloc(sizeof(struct Point2d));
    memset(p1, 0, sizeof(struct Point2d));
    p1->x = 10;
    p1->y = 20;
    struct Point2d *p2 = (struct Point2d *)malloc(sizeof(struct Point2d));
    memcpy(p2, p1, sizeof(struct Point2d));
    printf("%d %d\n", p1->x, p1->y);
    printf("%d %d\n", p2->x, p2->y);
    free(p1);
    return 0;
}
