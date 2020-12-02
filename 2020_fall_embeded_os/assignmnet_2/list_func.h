#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define LIST_FILE_NAME "_file_list.lst"

// for now it just print
// we will make a file with name file_list.lst for server side use.
//with arguments username & ip address

void mklistf(const char *username, const char *ipinfo)
{
    FILE *fp;
    char *cwd = (char *)malloc(sizeof(char) * 1024);
    char filename[256];
    DIR *dir = NULL;
    struct dirent *entry = NULL;

    //파일 내용을 채울 임시 버퍼
    char buf[100];
    //파일 정보 구조체
    struct stat info;
    getcwd(cwd, 1024);
    //for making list information file
    strcpy(filename, username);
    strcat(filename, LIST_FILE_NAME); //to make USER1_file_list.lst
    fp = fopen(filename, "w+");       //with overwriting mode
    if ((dir = opendir(cwd)) == NULL)
    {
        printf("current directory error\n");
        exit(1);
    }
    while ((entry = readdir(dir)) != NULL)

    {
        lstat(entry->d_name, &info);
        if (S_ISREG(info.st_mode))
        {
            printf("FILE : %s\n", entry->d_name);
            strcat(buf, username);
            strcat(buf, " ");
            strcat(buf, ipinfo);
            strcat(buf, " ");
            strcat(buf, entry->d_name);
            strcat(buf, "\n");
            fputs(buf, fp);
            memset(buf, 0, 100);
        }
        else if (S_ISDIR(info.st_mode))
        {
            printf("DIR : %s\n", entry->d_name);
        }
        else
        {
            printf("this is not a file or directory !\n");
        }
    }
    free(cwd);
    closedir(dir);
    fclose(fp);
}