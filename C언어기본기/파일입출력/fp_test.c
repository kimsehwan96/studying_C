#include <stdio.h>

int main(void){
    char s[20] = "Hello world";
    FILE *fp;
    fp = fopen("temp.txt", "w");
    fprintf(fp, "%s\n", s);
    fclose(fp);
    return 0;
}