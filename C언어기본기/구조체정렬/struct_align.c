#include <stdio.h>

#pragma pack(push, 1) //1바이트 정렬
struct PacketHeader{
    char flags;
    int seq;
};
#pragma pack(pop)

int main(void){
    struct PacketHeader header;

    printf("%d\n", sizeof(header.flags));    // 1: char는 1바이트
    printf("%d\n", sizeof(header.seq));      // 4: int는 4바이트
    printf("%d\n", sizeof(header));          // 5: 1바이트 단위로 정렬했으므로 
                                             // 구조체 전체 크기는 5바이트

    return 0;  
}