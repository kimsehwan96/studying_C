#include <stdio.h>
#include <string.h>


int main () {
    char s[20]="hello";
    char c ='h';
    strcat(s, &c);
    printf("%s\n", s);
    return 0;
}