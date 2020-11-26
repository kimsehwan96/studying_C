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