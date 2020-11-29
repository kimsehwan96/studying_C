# 함수 포인터
- C언어세너느 함수의 이름을 이용해 특정한 함수를 호출함.
- 함수 이름은 메모리 주소를 반환함

```c
#include <stdio.h>

void function(){
    printf("It's my function");
}

int main (void){
    printf("%p\n", function);
    return 0;
}
```

- 함수 포인터는 특정한 함수의 반환 자료형을 지정하는 방식으로 선언 가능
- 함수 포인터를 이용하면 형태가 같은 서로 다른 기능의 함수를 선택적으로 사용 가능하다.

`반환 자료형(*이름)(매개변수) = 함수명;`

### 여러가지 함수 포인터 예제 코드

```c
// 매개변수 및 반환 자료형이 없는 함수 포인터.

// 함수는 메모리 주소를 가질 수 있다.
// 그래서 함수으 메모리 주소를 가질 수 있는 '함수포인터' 도 존재하는 것
// function() <- 함수를 호출하는거
// function <- 해당 함수 메모리 주소!
#include <stdio.h>

void myFunction(){
    printf("this is my function \n");
}

void yourFunction(){
    printf("this is your function \n");
}

int main(void){
    void(*fp)() = myFunction;
    // void     (*fp)      ()
    // 반환자료형  포인터이름  매개변수가 없음
    fp();
    fp = yourFunction;
    fp();
    return 0;
}

```

```c
#include <stdio.h>

int add(int a, int b){
    return a + b;
}

int mul(int a, int b){
    return a * b;
}

int main(void){
    int (*fp)(int, int);
    //반환 자료형 | 포인터 이름 | 매개변수들
    fp = add;
    printf("%d\n", fp(10, 20));
    fp = mul;
    printf("%d\n", fp(10, 20));

    return 0;
}

```

```c
#include <stdio.h>

void add (int* a){
    *a = (*a) + 10;
}

void mul (int* a){
    *a = (*a)*10;
}

int main(void){
    int a = 5;
    void (*fp)(int *) = add;
    fp(&a);
    printf("%d\n", a);
    fp = mul;
    fp(&a);
    printf("%d\n", a);

    return 0;
    
}
```

### typedef

- typedef를 이용해 함수 포인터 모양을 단순화 시켜주는 것도 가능

```c
#include <stdio.h>

typedef void (*FuncPtr)(int*);

void add (int* a){
    *a = (*a) + 10;
}

void mul (int* a){
    *a = (*a)*10;
}

int main(void){
    FuncPtr fp;
    int a = 5;
    fp = add;
    fp(&a);
    printf("%d\n", a);
    fp = mul;
    fp(&a);
    printf("%d\n", a);

    return 0;
    
}
```


### 다음 코드를 분석해보자

- 다음 코드는 함수 포인터를 두 함수들 (sin 혹은 cos) 중 하나를 다른 함수 (compute_sum)에서 간접적으로 작동시키기 위해 사용한다. 이 프로그램은 main 함수가 compute_sum 함수를 두번 호출함으로써 작동한다.


```c
#include <math.h>
#include <stdio.h>

// compute_sum은 인자로써 함수포인터를 받는다.
double compute_sum(double (*funcp)(double), double lo, double hi)
{
    double  sum = 0.0;

    // 함수포인터로부터 리턴받은 값을 계산한다.
    for (int i = 0;  i <= 100;  i++)
    {
        double  x, y;

        // 함수를 invoke 하기위해 함수포인터 사용
        x = i / 100.0 * (hi - lo) + lo;
        y = (*funcp)(x);
        sum += y;
    }
    return sum / 101.0;
}

int main(void)
{
    double  (*fp)(double);      // Function pointer
    double  sum;

    // sin() 함수를 함수포인터로써 사용
    fp = sin;
    sum = compute_sum(fp, 0.0, 1.0);
    printf("sum(sin): %f\n", sum);

    // cos() 함수를 함수 포인터로써 사용
    fp = cos;
    sum = compute_sum(fp, 0.0, 1.0);
    printf("sum(cos): %f\n", sum);
    return 0;
}
```


### 함수 포인터를 반환하여 사용하기

```c
#include <stdio.h>

int add(int a, int b){
    return a + b;
}

int(*process(char* a))(int, int){
    printf("result : %s \n", a);
    return add;
}

int main (void){
    printf("%d\n", process("10과 20을 더해보겠다")(10, 20));
    return 0;
}
```

- 보면... 함수 포인터를 선언했고, 예는 리턴이 int

## 자주 쓰이지 않는 슈퍼고급 문법