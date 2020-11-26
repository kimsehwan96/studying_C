#include <pcap/pcap.h>

#include <stdlib.h>

typedef struct mac_address
{

    u_char byte1;

    u_char byte2;

    u_char byte3;

    u_char byte4;

    u_char byte5;

    u_char byte6;

} mac;

#define ETHER_ADDR_LEN 6

struct ether_header

{

    u_char ether_dhost[ETHER_ADDR_LEN];

    u_char ether_shost[ETHER_ADDR_LEN];

    u_short ether_type;

} eth;

typedef struct ip_address

{

    u_char byte1;

    u_char byte2;

    u_char byte3;

    u_char byte4;

} ip_address;

typedef struct ip_header

{

    //u_char ip_leng:4;

    //u_char  ip_version:4;

    u_char ver_ihl; // Version (4 bits) + Internet header length(4bits)

    u_char tos; // Type of service

    u_short tlen; // Total length

    u_short identification; // Identification

    u_short flags_fo; // Flags (3 bits) + Fragment offset (13 bits)

    u_char ttl; // Time to live

    u_char proto; // Protocol

    u_short crc; // Header checksum

    ip_address saddr; // Source address

    ip_address daddr; // Destination address

    u_int op_pad; // Option + Padding

} ip_header;

typedef struct tcp_header

{

    u_short sport; // Source port

    u_short dport; // Destination port

    u_int seqnum; // Sequence Number

    u_int acknum; // Acknowledgement number

    u_char th_off; // Header length

    u_char flags; // packet flags

    u_short win; // Window Size

    u_short crc; // Header Checksum

    u_short urgptr; // Urgent pointer

} tcp_header;

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

main()

{

    pcap_if_t *alldevs;

    pcap_if_t *d;

    int inum;

    int i = 0;

    pcap_t *adhandle;

    char errbuf[PCAP_ERRBUF_SIZE];

    u_int netmask;

    char packet_filter[] = ""; // 사용자가 원하는 프로토콜 필터 정보를 넣을 수 있는 공간

    struct bpf_program fcode; // 특정 프로토콜만을 캡쳐하기 위한 정책정보 저장

    /*

  네트워크 디바이스 목록을 가져온다.

  alldevs에 리스트 형래토 저장되며, 에러시 errbuf에 에러 내용을 저장한다.

  에러시 에러문을 출력하고 프로그램 종료

*/

    if (pcap_findalldevs(&alldevs, errbuf) == -1)

    {

        fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);

        exit(1);
    }

    /*

  pcap_findalldevs()함수를 이용하여 네트워크 디바이스정보를 출력한다.

*/

    for (d = alldevs; d; d = d->next)

    {

        printf("%d. %s", ++i, d->name);

        if (d->description)

            printf(" (%s)\n", d->description);

        else

            printf(" (No description available)\n");
    }

    if (i == 0)

    {

        //printf("\nNo interfaces found! Make sure WinPcap is installed.\n");

        printf("\nNo interfaces found! Make sure LiPcap is installed.\n");

        return -1;
    }

    /*

  캡쳐할 네트워크 디바이스를 선택한다.

*/

    printf("Enter the interface number (1-%d):", i);

    scanf("%d", &inum);

    /* 입력값의 유효성 판다. */

    if (inum < 1 || inum > i)

    {

        printf("\nAdapter number out of range.\n");

        pcap_freealldevs(alldevs);

        return -1;
    }

    /* 사용자가 선택한 장치 목록을 선택 */

    for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++)
        ;

    /* 실제 네트워크 디바이스 오픈 */

    /*                   디바이스명, 최대캡쳐길이, 모든패킷캡쳐, read time, 에러내용 저장변수 */

    if ((adhandle = pcap_open_live(d->name, 65536, 1, 1000, errbuf)) == NULL)

    {

        fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);

        pcap_freealldevs(alldevs);

        return -1;
    }

    /*

  패킷 필터링 정책을 위해 pcap_compile()함수 호출

  사용자가 정의한 필터링 룰을 bpf_program 구조체에 저장하여 특정 프로토콜 패킷만 수집

*/

    if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0)

    {

        fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");

        pcap_freealldevs(alldevs);

        return -1;
    }

    /*

  pcap_compile() 함수내용을 적용하기 위해  pcap_setfilter() 함수가 사용된다.

*/

    if (pcap_setfilter(adhandle, &fcode) < 0)

    {

        fprintf(stderr, "\nError setting the filter.\n");

        pcap_freealldevs(alldevs);

        return -1;
    }

    // 디바이스 정보 출력

    printf("\nlistening on %s...\n", d->description);

    // 해제

    pcap_freealldevs(alldevs);

    /*

  pcap_loop() 함수를 호출하여 선택한 디바이스를 반복적으로 패킷을 캡쳐하는 역할을 한다.

adhandle : 할당받은 디바이스 특성

0 : 무한르프 

packet_handler는 이더넷 헤더를 출력하는 함수

*/

    pcap_loop(adhandle, 0, packet_handler, NULL);

    return 0;
}

/*

   packet_handler() 함수 이더넷 헤더를 출력하기 위한 내용을 정의.

 */

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)

{

    /*

  이더넷 헤더에서 ether_type(상위프로토콜 정보)은 이더넷 헤더 다음에 오는 프로토콜을 알려주는 값

*/

#define IP_HEADER 0x0800

#define ARP_HEADER 0x0806

#define REVERSE_ARP_HEADER 0x0835

    // int 형의 ptyep변수 선언

    unsigned int ptype;

    /*

  mac 구조체와 동일한 형태를 srcmac, destmac  

  (srcmac 송신자의 MAC주소를 저장.)

  (destmac 수신자의 MAC주소를 저장.)

*/

    mac *destmac;

    mac *srcmac;

    /*

  목적지 MAC주소를 저장할 수 있는 구조체인 destmac에 pkt_data(수집된 패킷정보가 저장되어 있으며,

  제일 앞은 이더넷 헤더의 시작위치)를 저장.

*/

    destmac = (mac *)pkt_data;

    /*

  발신자 MAC주소를 담을 수 있는 공간인 srcmac에 수집된 데이터의 시작시점인

  pkt_data에서 6바이트 더한 값을 저장. 즉 송신자의 MAC주소가 저장

*/

    srcmac = (mac *)(pkt_data + 6);

    /* 이더넷 헤더 정보를 담을 수 있는 공간인 ether_header구조체를 eth라고 별칭하였다. */

    struct ether_header *eth;

    /* 이더넷 헤더정보를 eth에 저장 */

    eth = (struct ether_header *)pkt_data;

    /* 다음에 따라오는 프로토콜 정보를 ntohs()함수에 넣어 변환을 시킨후 ptype에 저장 */

    ptype = ntohs(eth->ether_type);

    /* 구조체 ip_header를 ih로 별칭한다. */

    ip_header *ih;

    /* */

    u_int ip_len;

    /* ih에 IP헤더 정보를 저장한다. */

    ih = (ip_header *)(pkt_data + 14);

    /*

  버전과 헤더 길이 필드를 ver_ihl이라는 필드이름으로 합쳐서 사용하는데,

  이는 버전정보 필드는 제거하고, 헤더길이 필드만을 추출하기 위한 방식이다. 

*/

    ip_len = (ih->ver_ihl & 0xf) * 4;

    printf("*************** Ethernet Frame Header *****************\n");

    printf("\n");

    printf("\n");

    /* 발신지 MAC주소 출력 */

    printf("Destination Mac Address : %02x.%02x.%02x.%02x.%02x.%02x \n",

           destmac->byte1,

           destmac->byte2,

           destmac->byte3,

           destmac->byte4,

           destmac->byte5,

           destmac->byte6);

    printf("\n");

    /* 수신자 MAC 주소 출력 */

    printf("Source Mac Address      : %02x.%02x.%02x.%02x.%02x.%02x \n",

           srcmac->byte1,

           srcmac->byte2,

           srcmac->byte3,

           srcmac->byte4,

           srcmac->byte5,

           srcmac->byte6);

    printf("\n");

    /* 다음 프로토콜 정보 출력*/

    if (ntohs(eth->ether_type) == IP_HEADER)

    {

        printf("Upper Protocol is IP HEADER(%04x)\n", ptype);
    }

    else if (ntohs(eth->ether_type) == ARP_HEADER)

    {

        printf("Upper Protocol is ARP HEADER(%04x)\n", ptype);
    }

    else if (ntohs(eth->ether_type) == REVERSE_ARP_HEADER)

    {

        printf("Upper Protocol is REVERSE ARP HEADER(%04x)\n", ptype);
    }

    else

    {

        printf("Upper Protocol is Unknown(%04x)\n", ptype);
    }

    printf("\n");

    /* IP헤더에서 버전과 헤더 길이를 출력 */

    if (ntohs(eth->ether_type) == IP_HEADER)

    {

        printf("********************** IP Header ***********************\n");

        printf("\n");

        printf("\n");

        /* 

  IP헤더에서 목적지 및 발신지 IP정보를 가리키고 있는 필드인

  daddr, sadder의 정보를 이용하여 출력

*/

        printf("Destination IP Address : %d.%d.%d.%d \n",

               ih->daddr.byte1,

               ih->daddr.byte2,

               ih->daddr.byte3,

               ih->daddr.byte4);

        printf("\n");

        printf("Source IP Address : %d.%d.%d.%d \n",

               ih->saddr.byte1,

               ih->saddr.byte2,

               ih->saddr.byte3,

               ih->saddr.byte4);

        printf("\n");

        /*

  IP헤더 구조체에 필드 proto를 확인하면, IP헤더 다음에 따라오는 프로토콜 정보를 얻을 수 있다.

  이를 이용하여 헤당 프로토콜를 출력

*/

        if (ih->proto == 0x06)

        {

            printf("Upper Protocol is TCP\n");

            printf("\n");

            tcp_header *th;

            th = (tcp_header *)((u_char *)ih + ip_len);

#define SYN 0x02

#define PUSH 0x08

#define ACK 0x10

#define SYN_ACK 0x12

#define PUSH_ACK 0x18

#define FIN_ACK 0x11

            printf("*********************TCP header **********************\n");

            printf("\n");

            printf("\n");

            printf("Destination port number       : %d\n", ntohs(th->dport));

            printf("Source port number            : %d\n", ntohs(th->sport));

            if ((th->flags) == SYN)

            {

                printf("Flags                         : SYN\n");

                printf("\n");

                printf("\n");
            }

            else if ((th->flags) == PUSH)

            {

                printf("Flags                         : PUSH\n");

                printf("\n");

                printf("\n");
            }

            else if ((th->flags) == ACK)

            {

                printf("Flags                         : ACK\n");

                printf("\n");

                printf("\n");
            }

            else if ((th->flags) == SYN_ACK)

            {

                printf("Flags                         : SYN, ACK\n");

                printf("\n");

                printf("\n");
            }

            else if ((th->flags) == PUSH_ACK)

            {

                printf("Flags                         : PUSH, ACK\n");

                printf("\n");

                printf("\n");
            }

            else if ((th->flags) == FIN_ACK)

            {

                printf("Flags                         : FIN, ACK\n");

                printf("\n");

                printf("\n");
            }

            else

            {

                printf("Flags(Unknown)                : %04x\n", th->flags);
            }
        }

        else if (ih->proto == 0x11)

        {

            printf("Upper Protocol is UDP\n");

            printf("\n");
        }

        else if (ih->proto == 0x01)

        {

            printf("Upper Protocol is ICMP\n");

            printf("\n");
        }

        else

        {

            printf("Upper Protocol is Unknown\n");

            printf("\n");
        }
    }

    else

    {

        printf("******************* NO IP Header *********************\n");

        printf("\n");

        printf("\n");
    }

    printf("*******************************************************\n");

    printf("\n");

    printf("\n");

    printf("\n");

    printf("\n");

    printf("\n");
}

출처 : https : //sugerent.tistory.com/240 [MISTERY]

               출처 : https: //sugerent.tistory.com/240 [MISTERY]