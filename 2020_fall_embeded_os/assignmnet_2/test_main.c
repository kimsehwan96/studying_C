#include <stdio.h>
#include "my_ip.h"
#include "list_func.h"

int main () {
    char ip[40];
    char username[40] = "user1";
    myIp(ip);
    printf("%s", ip);
    mklistf(username, ip);
}