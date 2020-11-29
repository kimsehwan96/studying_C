#include <stdio.h>

struct PacketHeader {
    char flags; //1bytes
    int seq; //4byte
};

int main(void){
    struct PacketHeader header;
    printf("%d\n",sizeof(header.flags)); //char는 1바이트
    printf("%d\n",sizeof(header.seq)); // int는 4바이트
    printf("%d\n",sizeof(header)); // 구조체 전체 크기는 8바이트

    return 0;
}