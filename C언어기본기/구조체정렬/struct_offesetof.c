#include <stdio.h>
#include <stddef.h>

struct PacketHeader {
    char flags;
    int seq;
};

int main()
{
    printf("%d\n", offsetof(struct PacketHeader, flags));    // 0
    printf("%d\n", offsetof(struct PacketHeader, seq));      // 4

    return 0;
}