# 구조체 정렬
- 구조체의 크기를 확인하는 법
    - sizeof(struct 구조체)
    - sizeof(구조체별칭)
    - sizeof(구조체변수)
    - sizeof 구조체변수

```c
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
```

- 5바이트가 아닌 8바이트의 크기가 나온다.

- C언어에서 구조체를 정렬할 때 멤버 중에서 가장 큰 자료형의 크기의 배수로 정렬을 한다
- 즉 4바이트를 기준으로 정렬
- 이 때 정렬은 1바이트 char 뒤에 3바이트 패딩을 붙여서 정렬된다.

- 확인해보자

```c
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
```

- flags는 오프셋이 0
- int는 오프셋이 4
- 즉 flags는 1바이트고, 뒤에 3바이트는 패딩이 채워지고
    - 그 이후에 int가 온다 이말씀.

### 구조체 정렬 피하는 방법!
- Raw Socket등 네트워크 패킷 관련해서 많이 쓰는 것 같음
    - 실제 최근에 회사 업무 중 python socket을 사용하면서
    - 정렬과 관련한 이슈가 발생했었음.
        - struct 모듈 format문자를 지정할 때
            - 명시하지 않으면 자동으로 정렬이 들어가는 이슈가 있었다.
            - 'BiBB' 포맷으로 바이너리 pack을 하려고 했는데
            - B는 1바이트, i는 4바이트이기때문에 7바이트를 기대했는데, 정렬이 발생해서 10바이트가 채워졌었다.

```c
#pragma pack(push, 정렬크기)
#pragma pack(pop)
```
- 이렇게 피할 수 있다.

```c
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
```
