#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main(void){
    int fd;
    char buf[512];
    getcwd(buf, 512);
    strcat(buf, "/data");
    printf("%s \n", buf);
    return 0;
}
