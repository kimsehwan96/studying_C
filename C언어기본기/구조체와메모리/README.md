# 구조체와 메모리 활용하기

- 구조체의 멤버를 모두 초기화 하고 싶을 때

```c
구조체멤버.멤버1 = 0;
구조체멤버.멤버2 = 0;
구조체멤버.멤버3 = 0;
구조체멤버.멤버4 = 0;
```

- 비효율 적이니까. memset 활용

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Point2d {
    int x;
    int y;
};

int main(void){
    struct Point2d p1;
    memset(&p1, 0, sizeof(struct Point2d));
    printf("%d %d \n", p1.x, p1.y);
    return 0;
}
```

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Point2d {
    int x;
    int y;
};

int main(void){
    struct Point2d p1;
    memset((struct Point2d *)&p1, 0, sizeof(struct Point2d));
    printf("%d %d\n", p1.x, p1.y);
    return 0;
}
```

```c
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
    printf("%d %d\n", p1->x, p1->y);
    free(p1);
    return 0;
}
```

- 위 세가지 몸두 동일한 예제.

## 구조체와 메모리 복사하기
- 매번 내용이 같은 구조체 만들기 번거롭다.
- 이미 생성한 값을 저장한 구조체나 메모리를 복사하는 경우가 자주 있음
- memcpy를 이용하자.

- memcpy(목적지포인터, 원본포인터, 크기);
```c
void *memcpy(void *_Dst, void const *_Src, size_t _Size)
```

```c
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
    //struct Point2d p2; 로 선언하면
    //memcpy(&p2, p1, ~~) 이렇게 진행되어야 함 ㅋㅋ.
    memcpy(p2, p1, sizeof(struct Point2d));
    printf("%d %d\n", p1->x, p1->y);
    printf("%d %d\n", p2->x, p2->y);
    free(p1);
    return 0;
}
```

