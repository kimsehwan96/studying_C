#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY_NUM     9527
#define MEM_SIZE    1024

//기존에 생성된 공유메모리가 있으면 초기화 해야 함
//코드 마지막부분에 공유메모리 초기화 후 종료
void cleanup(int segment_id, char* shared_memory){
   //shmdt 공유 메모리를 해제하는 시스템콜
   shmdt(shared_memory);
   //공유 메모리 내용을 삭제, NULL로 만듦
   shmctl(segment_id, IPC_RMID, NULL);
}

int main(void) {

    int shm_id;
    void *shm_addr;
    int i;
    //int shmget(key_t key, size_t size, int shmflg)
    //key : 임의 숫자 또는 ftok으로 생성한 키값
    //size -> 공유 메모리 크기
    //shmflg -> 공유 메모리 속성
    // 리턴 -> 공유 메모리 식별자 리턴
     if ( -1 == ( shm_id = shmget( (key_t)KEY_NUM, MEM_SIZE, IPC_CREAT|0666))){
        printf("공유메모리 생성 실패\n");
        return -1;
     }


   //void *shmat(int shmid, const void *shmaddr, int shmflg);
   //shmid : shmget으로 얻은 공유메모리 식별자
   //shmaddr : 공유 메모리 연결 주소 (char *)NULL 로 설정하면 알아서 연결
   //shmflg : 공유 메모리의 읽기/ 쓰기 권한 (0이면 읽기,쓰기 가능, SHM_RDONLY면 읽기만 가능)
   //리턴 값 : 성공시 연결된 공유 메모리의 시작 주소를 리턴
    if ( ( void *)-1 == ( shm_addr = shmat( shm_id, ( void *)0, 0)))
    {
       printf( "공유 메모리 첨부 실패\n");
       return -1;
    }

   for(i = 0; i < 10000000; i++)
   {
      sprintf((char *)shm_addr, "Send Message[%i]", i);       // 공유 메모리에 카운터 출력
   }
   sprintf((char *)shm_addr, "exit"); 
   cleanup(shm_id, shm_addr);

    return 0;
}

/*
공유 메모리 사용법

printf("%s\n", (char *)shmaddr); 포인터 변수처럼 사용

strcpy((char *)shmaddr, "Hello world");
공유 메모리에 쓰기.. 메모리에 쓰는 여러 방법중 하나를 사용하면 됨..
memset, sprintf, strcpy 등등등


shmid : shmget으로 생성한 공유메모리 식별자
cmd : 수행할 제어 기능 IPC_RMID -> 공유 메모리 제거
buf ->제어 기능에 사용되는 메모리 구조체의 구조
int shmctl(int shmid, int cmd, struct shmid_ds *buf);

*/