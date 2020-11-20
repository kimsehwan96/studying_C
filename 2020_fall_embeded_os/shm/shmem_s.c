#include <stdio.h>      // printf()
#include <unistd.h>     // sleep()
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <time.h>

#define  KEY_NUM     9527
#define  MEM_SIZE    1024

//기존에 생성된 공유메모리가 있으면 초기화 해야 함
//코드 마지막부분에 공유메모리 초기화 후 종료
void cleanup(int segment_id, char* shared_memory){
   shmdt(shared_memory);
   shmctl(segment_id, IPC_RMID, NULL);
}

int main( void)
{
   int   shm_id;
   void *shm_addr;
   double startTime, endTime, benchmark;

   if ( -1 == ( shm_id = shmget( (key_t)KEY_NUM, MEM_SIZE, IPC_CREAT|0666)))
   {
      printf( "공유 메모리 생성 실패\n");
      return -1;
   }

   if ( ( void *)-1 == ( shm_addr = shmat( shm_id, ( void *)0, 0)))
   {
      printf( "공유 메모리 첨부 실패\n");
      return -1;
   }


   //waiting for start signal 

   startTime = (float)clock()/CLOCKS_PER_SEC;
   for(;;)
   {
        printf( "%s\n", (char *)shm_addr);    // 공유 메모리를 화면에 출력
        if (strcmp((char *)shm_addr, "exit") ==0){
        endTime = (float)clock()/CLOCKS_PER_SEC;
        benchmark = endTime - startTime;
        printf("total processed time %.3lf 초\n", benchmark);
        cleanup(shm_id, shm_addr);
        return 0;
      }
    }


   return 0;
}