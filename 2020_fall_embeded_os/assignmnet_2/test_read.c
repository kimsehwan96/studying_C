#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define BUFSIZE 512

int main(){
    int fd;
    int n_bytes = 0;
    char *buf = (char *)malloc(BUFSIZE);
    fd = open("user1_file_list.lst", O_RDWR);
    printf("this is fd %d \n", fd);

    while((n_bytes = read(fd, buf, BUFSIZE)) > 0){
        printf("%s \n", buf);
    }

    free(buf);
    close(fd);
    return 0;
    
}