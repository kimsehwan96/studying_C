# 포인터 변수

* 포인터 변수는 *를 사용하여 선언한다.
` 자료형 *포인터이름;`
` 포인터 = &변수;`

즉 포인터 변수는 특정한 `메모리 번지`를 저장하는 변수라고 할 수 있다.

```c
#include <stdio.h>

int main() {
    int *numPtr == NULL; //포인터 변수 선언
    int num1 = 10; //변수를 선언하고 10 저장
    numPtr = &num1; //포인터 변수는 특정한 메모리 번지를 저장하는 변수이므로 num1의 메모리 번지를 저장
    // *numPtr 을 출력하면, 해당 메모리에 저장된 값을 출력 가능하고, numPtr 출력하면 메모리 번지가 출력
}
```

```c

#include <stdio.h>

void add(int a, int b, int *sum) {
    *sum = a + b;
}

int main(void) {
    int a = 5;
    int b = 3;
    int sum = 0;
    add(a, b, &sum);
    printf("%d\n", sum);
    return 0;
}
``` 

이런식으로 구현하면... 메모리 번지를 받아서 메모리 번지에 저장된 `값` (주소값이 아닌, 해당 주소에 저장된 값)을 참조하고, 변화시킬 수 있다.

