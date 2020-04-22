#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int a,b;
    scanf( "%d %d" , &a, &b);

    a = b*2;
    b = a/2;
    sort(a,b);

    printf("%d %d", a, b);
    return 0;
}