#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>


int main () {
    char *cwd = (char *)malloc(sizeof(char)*1024);
    DIR *dir = NULL;
    struct dirent *entry = NULL; 
    //파일 정보 구조체
    struct stat info;
    getcwd(cwd, 1024);

       if( (dir = opendir(cwd)) == NULL)
        {
                printf("current directory error\n");
                exit(1);
        }
        while((entry = readdir(dir)) != NULL)

        {
                lstat(entry->d_name, &info);
                if(S_ISREG(info.st_mode)){
                    printf("FILE : %s\n", entry->d_name);
                }
                else if (S_ISDIR(info.st_mode)){
                    printf("DIR : %s\n", entry->d_name);
                }
                else {
                    printf("this is not a file or directory !\n");
                }

        }
        free(cwd);
        closedir(dir);
        return 0;
}