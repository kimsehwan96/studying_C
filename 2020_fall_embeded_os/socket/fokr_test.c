#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    int i;
    
    pid_t pid;
    
    pid = fork();
    
    if (pid ==0){
        for (i=0; i<10; i++){
            printf("childe %d\n", i);
            sleep(1);
        }
        exit(0);
    }
    else if (pid >0){
        for(i=0; i<10; i++){
            printf("parent: %d\n", i);
            sleep(2);
        }
        exit(0);
    }
    else{
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(1);
    }
    return 0;
}
