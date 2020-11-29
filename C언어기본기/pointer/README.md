# 포인터 변수

* 포인터 변수는 *를 사용하여 선언한다.
` 자료형 *포인터이름;`
` 포인터 = &변수;`

즉 포인터 변수는 특정한 `메모리 번지`를 저장하는 변수라고 할 수 있다.

즉 포인터 변수도 변수이며, 담고있는 값이 `메모리 번지` 이다.
- 포인터 변수도 변수 자체의 주소를 갖고있다 (포인터 변수에 담긴 주소와 별개로.)

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


```c
#include <stdio.h>
#include <limits.h>

int add(int x, int y){
    return x + y;
}

int main(void) {
    int *a; // 정수형 변수의 메모리 번지를 담을 수 있는 포인터 선언
    int b = 0; // 정수형 변수 선언
    int c = 20;
    int d = 30;
    a = &b; // 포인터변수 a의 값으로, 정수형 변수 b의 주소를 저장
    *a = add(c, d); //*는 간접 참조 연산자(포인터 변수가 가리키는 변수를 구함) 즉, *a는 b와 동일한 의미.
    //즉 위의 코드는 b = add(c,d); 와 완전하게 동일하다.
    printf("%d\n", *a);  //간접 참조 연산자를 통해 포인터 변수 a가 가르키는 주소에 저장된 변수의 '값'을 읽어낸대 (b를 읽는다는 의미)
    printf("%d\n", b); //b의 값을 바로 프린트 해본다
    // 결과는 동일하다
    return 0;
}

```

- 포인터 변수를 선언할때의 *와, 사용할때의 *은 완전히 다른 용도이다.

## macos & linux 에서 메모리 주소 확인
- 일반적인 window os예제에서는 %d로도 주소를 포매팅 출력하지만, 
- 맥과 linux에서는 &p로 합시다.

```c
#include <stdio.h>
#include <limits.h>

int main(void) {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i;
    
    for(i = 0; i < 10; i++){
        printf("%p\n", &a[i]);
    }
    return 0;
}
```

```console

0x7ffeefbff490
0x7ffeefbff494
0x7ffeefbff498
0x7ffeefbff49c
0x7ffeefbff4a0
0x7ffeefbff4a4
0x7ffeefbff4a8
0x7ffeefbff4ac
0x7ffeefbff4b0
0x7ffeefbff4b4

```
- 4byte 짜리 자료형인 int를 배열로써 10개 선언했기 때문에 뒤에 4byte씩 증가함.
- 그리고 배열 자체의 메모리 주소 참조하라고 하면 맨 첫번쨰 주소만 `0x7ffeefbff490` 요거 출력되어요


### 포인터의 강력한 기능
- 포인터는 컴퓨터 시스템의 특정한 메모리에 바로 접근 할 수 있다.
- 기존에 존재하던 중요한 메모리 영역에 접근하지 않도록 해야 함.
- 즉, 메모리 주소 번지를 직접 할당
```c
int *a = 0x312412412414;
```
과 같은건, 내가 해당 메모리 번지를 정확히 어떤 용도로 쓰는지 모르면 하지 말자


### 이중 포인터

```c
#include <stdio.h>
#include <limits.h>

int main(void) {
    int a =5;
    int *b = &a;
    int **c = &b;
    printf("%d\n", **c);
    return 0;
}
```

즉 포인터 변수도 결국 자신이 할당된 메모리 번지가 있기 떄문에, 이중 포인터, 삼중 포인터 모두 가능


### 배열

- 배열과 포인터는 내부적으로 동일하고
- 배열을 선언한 이후에는 배열 변수 자체가 포인터가 된다

```c
#include <stdio.h>
#include <limits.h>

int main(void) {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *b = a;
    printf("%d\n", b[0]);
    printf("%p\n", b);
    printf("%p\n", &a[0]); //바로 위 문장과 동일한 내용 출력.
}
```
배열 변수 a 자체가 저 연속된 자료의 첫번째 메모리 번지를 가지는 포인터로써 쓰인다.


 

