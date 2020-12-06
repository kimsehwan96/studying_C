# 파일 입출력 (저수준 인터페이스)

- 파일 입출력을 다루는 가장 간단한 방법인 시스템 콜을 자세히 알아보겠다.

- 파일은 읽거나 쓰기 전에 반드시 열어야 한다.
- 커널은 파일 테이블이라는 프로세스별로 열린 파일 목록을 관리한다.
- 이 테이블은 음이 아닌 정수값인 파일 디스크립터로 인덱싱 되어있다.
- 이 테이블의 각 항목은 열린 파일에 대한 정보를 갖고있고, 메모리에 복사된 inode를 가리키는 포인터와 각종 메타데이터가 포함되어있다.

- 파일디스크립터는 C의 int 자료형이다.

- 파일 디스크립터는 단순히 일반 파일만 나타내는 것이 아니다. 장치파일, 파이프, 디렉터리, 퓨텍스, FIFO, 소켓 접근에도 사용되며 모든 것이 파일이라는 유닉스 철학에 따른다.

- 자식 프로세스는 부모프로세스가 소유한 파일테이블의 복사본을 상속받는다.
- 열린 파일, 접근 모드, 현재 파일의 오프셋 등을 담고 있는 목록은 동이하지만, 자식 프로세스가 파일을 닫는다고, 다른 프로세스의 파일 테이블에 영향을 미치지는 않는다.

### 파일 열기
- 파일에 접근하는 가장 기본적인 방법은 read()와 write()시스템 콜이다.
- 그 전에 open()이나 creat() 시스템 콜을 사용해 파일을 열어두고,
- 다 쓰면 close()시스템 콜로 파일을 닫아야 한다.

### open() 시스템 콜
- open()시스템 콜을 이용하여 파일을 열고, 파일 디스크립터를 얻는다. 

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *name, int flags);
int open(const char *name, int flags, mode_t mode);
```

- 경로 이름이 name인 파일을 파일디스크립터에 ㅁ맵핑하고, 성공하면 파일 디스크립터를 반환
- 파일ㄹ 오프셋은 파일의 시작지점인 0으로 설정되며, 파일은 flags로 지정한 플래그에 대응하는 접근모드로 열리게 된다.

### open() 플래그
- flag 인자는 O_RDONLY, O_WRONLY, O_RDWR 중 하나를 포함해야 한다.
- 각 프래그는 읽기 전용모드, 쓰기 전용 모드, 읽기와 쓰기 모드로 파일을 열도록 요청한다.


### 새로운 파일의 권한
- flags에 O_CREAT 인자를넣었을 경우, mode 인자로 권한을 설정해주지 않으면 골치를 겪을 수 있다. 0644(소유자는 읽기쓰기, 나머지는 읽기만) 권한을 주로 사용하겠지

```c
int fd;
fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 06444)
if (fd == -1)
/* 에러 발생 */

### creat()함수

```c
int creat(const char *name, int mode)
{
    return open(name, O_WRONLY | O_CREAT | O_TRUNC, mode);
}
```

위와 같이 직접 구현 할수도 있지만, creat 시스템콜이 애초에 있으므로 사용하도록 하자.

### read()로 읽기
- 이제 파일을 어떻게 여는지 알았으므로, 읽는 방법을 확인해보자.
- read() 시스템 콜을 사용하는 방법이 있다.

```c
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t len);
```

- 호출 할 때 마다 fd가 참조하는 파일의 현재 파일 오프셋에서 len 바이트만큼 buf로 읽어들인다. 성공하면 buf에 쓴 바이트 숫자를 반환한다.

### 반환값
- read()가 len보다 작은 양수 값을 반환하는 경우도 있다. 이런 현상에는 몇가지 이유가 있다. (내가 계속 텀플하면서 겪은 이슈)
- len 바이트보다 작은 바이트만 사용 가능하거나, 시그널이 시스템 콜을 중단시키거나, fd가 파이프라면 파이프가 깨지는 등 이유는 다양하다.

- read()를 사용할 때 반환값이 0이 될 또 다른 가능성을 고려해야 한다.
- read()함수는 파일의 끝(EOF)를 알려주기 위해 0을 반환한다.
- 이 경우 당연히 읽을 바이트가 남아있지 않다. EOF는 에러로 취급되지 않는다.
- 단순히 파일 오프셋이 파일에서 마지막 유효한 오프셋을 넘어갔기 때문에 더이상 읽을 데이터가 없다는 사실을 알려줄 뿐이다.

- 파일 끝에 도달한것과 달리 len바이트만큼 읽으라고 요청했지만, 읽을 데이터가 없다면 read()호출은 읽을 바이트가 생길 때 까지 블록(잠자기)된다.

- EOF를 반환하는 앞선 동작과는 많이 다른 동작이다.

- 따라서 사용 가능한 데이터가 없음과 파일 끝 사이에는 차이점이 존재한다.

- 블록은 읽기 과정에서 더 많은 데이터를 기다림을 의미한다. (소켓이나 디바이스 파일에서 읽는 경우가 이에 해당한다.)

- 어떤 에러는 복구 가능하다. 예를 들어 한 바이트도 읽기 전에 시그널이 read()를 중단 시켰을 경우 read()는 -1을 반환하며 errno을 EINTR로 설정한다. 
- 이 경우 한번 더 읽기가 가능!


### read()호추의 다양한 문제점(가능성)
1. 호출이 len과 같은 값을 반환한다. len바이트를 전체를 읽어서 buf에 저장했다. 의도한 결과다
2. 호출이 len보다는 작지만 0보다는 큰 값을 반환한다. 읽은 바이트는 buf에 저장된다.
    - 시그널이 중간에 읽기를 중단시켰거나
    - 읽는 도중에 에러가 발생해서 1바이트 이상이지만 len길이 만큼 데이터를 가져오지 못했거나
    - len바이트를 읽기 전에 EOF에 도달한 경우에 발생한다.
    - 적저하게 buf와 len값을 고친다음에 read()를 호출하면 남은 바이트를 남은 버퍼 공간에 읽거나 에러 원인을 확인 할 수 있다.

3. 0을 반환한다. 이는 EOF를 나타낸다. 더 이상 읽을 데이터가 없다
4. 현재 사용 가능한 데이터가 없기 때문에 호출이 블록된다. 논블록모드에서는 이런 상황이 발생하지 않는다.
5. 호출이 -1을 반환하고 errno을 EINTR로 설정한다. (바이트를 읽기전에 시그널이 도착한 상황이고, 다시 읽기 시도하면 된다)
6. -1을 반환하고 EAGAIN으로 설정한다. EAGAIN은 현재 읽을 데이터가 없기 때문에 블록된 상태이며, 나중에 반드시 다시 읽기 요청을 해야 한다고 알려준다. 논 블록 모드에서만 발생
7. 호출이 -1을 반환하고 errno을 위 두 경우와 다른값으로 설정한다 -> 이는 심각한 에러가 발생했음을 의미한다.

### 전체 바이트 읽기 ******* 매우 중요 **********
```c
ssize_t ret;

while(len != 0 && (ret = read(fd, buf, len)) != 0) { //남은 길이가 0 이 아닐때 그리고, ret이 0이 아닌 값일때 이 루프는 계속 진행된다.
    if (ret == 0-1) {
        if(errno == EINTR)
            continue;
        perror("read");
        break;
    }
    len -= ret;
    buif += ret;
}
```


- 실제 사용 예:
```c
/*
파일명 : all_data_read.c
컴파일 및 실행 : gcc -c all_data_read.c && gcc -o all_data_read all_data_read.o && ./all_data_read
내용 : 파일을 열고, 파일의 전체 바이트를 읽는 함수이다.
len 바이트만큼 모두 읽기를 시도하고, len 만큼 읽기 전에 EOF를 만나면 종료되는 코드 조각이다.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

extern int errno;

int main(void){
    int fd, len;
    char *buf = (char *)malloc(512);
    ssize_t ret;

    len = 65536; //그냥 긴 값 테스트
    fd = open("test.file", O_RDONLY);
    if (fd == -1){
        perror("open");
    }
    while(len != 0 && (ret = read(fd, buf, len)) != 0) {
        printf("%s", buf);
        if (ret == -1){
            if(errno == EINTR)
                continue; //한번 더 실행
            perror("read"); //다른 에러에 대해서는 break
            break;
        }
        len -= ret; //길이에서 ret된 값 만큼 뺀다.
        buf += ret; //버퍼의 포인터 연산(증가)시킨다.
    }
    printf("\nread done : left len : %d\n", len);

    close(fd);
    free(buf);
    return 0;
}
```

### 논블록 읽기
- 프로그래머 입장에서 읽을 데이터가 없을 때 read() 호출이 블록되지 않기를 바라는 경우가 있다.(지금 내경우 ㅠㅠㅠㅠㅠ)
- 블록되는 대신, 읽을 데아터가 없다는 사실을 알려주기 위해 호출이 즉시 반환되는 편을 선호한다.
- 이를 논블록 입출력이라고 한다.
- 논블록 입출력은 애플리케이션이 잠재적으로 다중 파일 입출력을 수행하도록 만든다.
- 따라서 특정 파일에서 블록되는 바람에 다른 파일에서 사용 가능한 데이터를 놓치는 현상이 발생하지 않음.

- errno 값인 EAGAIN을 점검할 필요가 있다. 
- 이때 파일은 O_NONBKOCK을 모드로 넘겨서 열어야 한다.
- 파일 디스크립터를 논블록 모드로 열고 읽을 데이터가 없다면 read()호출은 블록되는 대신 -1을 반환한다 또한 errno을 EAGAIN으로 설정한다.
- 논블록 읽기를 수행할 때에는 EAGIAN을 반드시 점검해야 한다.

### read()크기 제약
- POSIX에서는 size_t와 ssize_t 타입을 지원한다.
    - size_t 타입은 바이트 단위로 크기를 측정하기 위해서 사용되는 값
    - ssize_t는 부호가있는 size_t 타입으로, 음수는 에러를 포함하기 위해 사용된다.
    - 대다수 리눅스 시스템에서 SSIZE_MAX는 LONG_MAX이다. 32bit 기계에서는 0x7fffffff임.

### write()로 파일 쓰기

- 파일에 데이터를 기록하기 위해 사용하는 가장 기본적이며 일반적인 시스템 콜은 write()이다.
- write()는 read()와 반대개념의 시스템 콜이며 역시 POSIX 표준이다.

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

- write() 호출은 count 바이트 만큼 파일 디스크립터 fd가 참조하는 파일의 현재 파일 위치에 시작 지점이 buf인 내용을 기록한다.
- 성공하면 쓰기에 성공한 바이트 수를 반환하며, 파일 오프셋도 같은 크기만큼 전진한다.
- 에러가 발생하면 -1을 반환하고, errno을 적절한 값으로 설정한다. write()호출이 0을 반환 할 수도 있지만, 의미없다.


### 부분 쓰기
- write()시스템 콜은 read()시스템 콜에서 발생하는 부분 읽기와 비교해 부분 쓰기를 일으킬 가능성이 훨씬 적다.
- EOF조건도 없다, 일반 파일에 대한 write()는 에러가 발생하지 않을 경우 요청받은 전체 쓰기 작업 수행을 보장한다.
- 따라서 일반 파일을 대상으로 작업을 수행할 때에는 루프내에서 돌릴 필요가 없다.
- 소켓같은 다른 파일 유형을 대상으로 할 경우에는 루프가 필요할지도 모른다.

```c
ssize_t ret, nr;

while(len != 0 && (ret = write(fd, buf, len)) != 0){
    if(ret == -1) {
        if (errno = EINTR)
            continue;
        perror("write");
        break;
    }
    len -= ret;
    buf += ret;
}
```

### 파일 닫기
- 파일 디스크립터로 읽고 쓰는 작업을 마치면 close()시스템 콜로 파일 맵핑을 끊어야 함ㄴ.

### lseek()로 탐색하기.

- 보통 파일 입출력은 파일 전체에 걸쳐 선형적으로 발생하고, 읽기와 쓰기 중에 자연스럽게 발생하는 파일 위치 갱신이면 족하다.
-  하지만 어떤 경우에는 파일의 특정 위치로 직접 이동해야 할 필요가 있다. lseek()시스템 콜을 사용해서 파일 오프셋을 특정 값으로 지정하는 것도 가능.
- 어떤 입출략도 발생시키지 않는다.

```c
#include <sys/types.h>
#include <unistd.h>

off_t lseek (int fd, off_t pos, int origin);
```

- lseek()는 origin 인자에 따라 다음과 같이 동작한다.
    - SEEK_CUR : fd의 파일 오프셋을 현재 오프셋에서 pos를 더한 값으로 설정한다. pos가 0 이면 현재 파일 오프셋을 반환
    - SEEK_END : fd의 파일 오프셋을 현재 파일 크기에서 pos를 더한 값으로 설정한다. pos가 0 이면 현재 파일의 끝으로 설정
    - SEEK_SET : fd의 파일 오프셋을 pos값으로 설정한다, pos가 0 이면 파일의 처음으로 설정

- 실제 사용해보았다.

```c
/*
파일명 : read_file_size.c
컴파일 및 실행 : gcc -c read_file_size.c && gcc -o read_file_size read_file_size.o && ./read_file_size
lseek()을 이용하여 파일의 끝과 처음으로 이동하며 파일의 크기를 체크한다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

extern int errno;

int main(void){
    int fd, pos;

    fd = open("test.file", O_RDONLY);
    if (fd == -1){
        perror("open");
    }
    pos = lseek(fd, 0, SEEK_END); //파일의 끝으로 이동하고 그 오프셋을 반환받아 pos에 저장
    if (pos == (off_t) -1)
        perror("seek");
    lseek(fd, 0, SEEK_SET); //원래 파일 오프셋으로 이동
    printf("%s's file size is : %d", "test.file",pos); // pos 결과값 857 , 실제 파일 사이즈 857바이트. (이걸 이용하면 사이즈 체크후 소켓에서 처리하기 편할거같은뎅)
    close(fd);
    return 0;
}
```

# 다중 입출력 ****** 매우 짱 중요 *********

- 키보드 입력(stdin)과 프로세스간 통신(IPC), 그리고 여러 파일 사이에서 일어나는 입출력을 처리하면서
- 하나 이상의 파일 디스크립터를 블록할 필요가 있다.
- 이벤트 드리븐 GUI 어플리 케이션은 메인 루프에서 수백개의 이벤트와 씨름한다....(어렵겠다)
- 단일 프로세스는 각 파일 디스크립터를 분리해서 서비스하는 스레드 없이는 동시에 하나 이상의 파일 디스크립터를 블록할수 없다.
- 하지만 개중에 하나라도 대응할 준비가 안되어 있다면, read()시스템콜 호출했는데 데이터를 기다리고 있다면,프로세는 블록되고 더는 다른 파일 디스크럽터를 처리 할 수 없다

- 다중 입출력을 살펴보자
    - 다중 입출력은 애플리케이션이 여러개의 파일 디스크립터를 동시에 블록하고 그중 하나라도 블록되지 않고 쓸 준비가 되면 알려주는 기능을 제공한다.
        1. 다중 입출력 : 파일 디스크립터중 하나가 입출력이 가능 할 때 알려준다
        2. 준비가 됐나? 준비가 된 파일 디스크립터가 없다면 파일 디스크립터가 준비될 때 까지 잠든다.
        3. 깨어나기.. 어떤 파일 디스크립터를 준비해놓았니?
        4. 블록하지 않고 모든 파일 디스크립터가 입출력을 준비하도록 관리한다
        5. 1로 돌아가서 다시 시작한다.

- 리눅스는 select, poll, epoll 같은 인터페이스를 제공하고, 이와 비슷하게 윈도우는 iocp를 제공한다.(게임 업계에서 많이 쓰는 것 같더라 얘기 들어보니)

### select()
- 동기화된 다중 입출력 메커니즘을 제공한다.

```c
#include <sys/select.h>

int select (int n, 
    fd_set *readfdfs,
    fd_set *writefds,
    fd_set *exceptfds,
    struct timeval *timeout);

FD_CLR(int fd, fd_set *set);
FD_ISSET(int fd, fd_set *set);
FD_SET(int fd, fd_set *set);
FD_ZERO(fd_set *set);
```

- select() 호출은 파일 디스크립터가 입출력을 수행할 준비가 되거나 옵션으로 정해진 시간이 경과할 때 까지만 블록된다.

- 감시 대상 파일 디스크립터는 세가지 집합으로 나뉘어 각각 다른 이벤트를 기다린다.
    - readfds 집합의 파일 디스크립터는 데이터 읽기가 가능한지 (블록 되지 않고 read()작업이 가능한지)를 파악하기 위해 감시한다.
    - writefds 집합의 파일 디스크립터는 블록되지 않고 write()작업이 가능한지 감시한다.
    - 마지막으로 exceptfds 집합의 파일 디스크립터는 예외가 발생했거나 대역을 넘어서는 데이터(소켓에만 적용)가 존재하는 지 감시한다.
    - 어떤 집합이 NULL이라면 select()는 해당 이벤트를 감시하지 않는다.
- 호출이 성공하면 각 집합은 요청받은 입출력 유형을 대상으로 입출력 준비된 파일 디스크립터만 포함하도록 변경된다.

- 첫번째 인자인 n은 파일 디스크립터 집합에서 가장 큰 파일디스크립터 숫자에 1을 더한 값이다.
- timeout 인자는 timeval 구조체를 가리키는 포인터이며 이 구조체는 다음과 같이 정의되어있다.

```c
#include <sys/time.h>

struct timeval {
    long tv_sec;
    long tv_usec;
}
```

- 이 인자가 NULL이면 select() 호출은 입출력이 준비된 파일 디스크립터가 없을 경우에도
- tv_sec초와 tv_usec초 이후에 반환된다.

- timeout에 설정된 두 값이 모두 0이면 호출은 즉시 반환되며 호출하는 시점에서 대기중인 이벤트를 알려주지만
- 그 다음 이벤트를 기다리지는 않는다.

- FD_ZERO는 지정한 집합 내의 모든 파일 디스크립터를 제거한다. 항상 select()를 호출하기 전에 사용한다.
```c
fd_set writefds;

FD_ZERO(&writedfs);
```

- FD_SET은 주어진 집합에 파이 디스크립터를 추가하고, D_CLR매크로는 주어진 집합에서 파일 디스크립터를 하나 제거한다.
```c
FD_SET(fd, &writefds);
FD_CLR(fd, &writefds);
```

- FD_ISSET 매크로는 파일 디스크립터가 주어진 집합에 존재하는지 검사한다.
- select()호출이 반환 된 다음에 파일 디스크립터가 입출력이 가능한 상태인지 확인하기 위해 사용ㄴ한다.

```c
if (FD_ISSET(fd, &readfds))
    /* fd에서 즉시 값을 읽을 수 있다 */
```


### select() 예제 
- 이 예제는 5초동안 stdin으로 들어온 입력을 기다리며 블록된다.
- 파일 디스크립터 하나만 감시하므로 실제로 다중 입출력을 수행하진 않음

```c
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define TIMEOUT 5 /* 타임아웃 (초) */
#define BUF_LEN 1024 /* 읽기 버퍼 사이즈 (바이트) */

int main(void) {
    struct timeval tv;
    fd_set readfds;
    int ret;

    /* 표준 입력에서 입력을 기다리기 위한 준비*/
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    /* select가 5초 기다리도록 timeval 구조체 설정 */
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;

    /* 입력 기다리기 */
    ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
    if(ret == -1) {
        perror("select");
        return 1;
    } else if (!ret) {
        printf("%d seconds elapsed \n", TIMEOUT);
        return 0;
    }

    /* 
    * 여기까지 오면 select가 0이 아닌 양수를 반환 했다는 의미로, 파일디스크립터에서 읽기 가능
    */

   if (FD_ISSET(STDIN_FILENO, &readfds)) {
       char  buf[BUF_LEN+1];
       int len;

       /*
            여기서는    read() 블록되지 않는다,
       */
      len = read(STDIN_FILENO, buf, BUF_LEN);
      if(len==-1) {
          perror("read");
          return 1;
      }
      if(len){
          buf[len] = '\0';
          printf("read : %s\n", buf);
      }
      return 0;
   }

}
```


### poll 예제

- poll 시스템 콜은 시스템 V에서 제공하는 다중 입출력 방식.

```c
#include <poll.h>
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

- select와 달리, poll은 fds가 가리키는 단일 pollfd 구조체 배열을 nfds 개수만큼 사용한다.

```c
#include <poll.h>

struct pollfd {
    int fd; //감시할 파일 디스크립터
    short events; //감시할 이벤트
    short revents; // 발생한 이벤트
};
```

- 각 pollfd 구조체는 감시하고자 하는 단일 파일디스크립터를 명시한다.
- events 필드는 그 파일 디스크립터에서 감시할 이벤트의 비트 마스크이다.
- events 필드에서 요청한 모든 이벤트가 revents에 담겨서 반환 될 수도 있다.

- 설정 가능한 이벤트 목록
    1. POLLIN : 읽을 데이터가 존재한다.
    2. POLLRDNORM : 일반 데이터를 읽을 수 있다.
    3. POLLDBAND : 우선권이 있는 데이터를 읽을 수 있다.
    4. POLLPRIO : 시급히 읽을 데이터가 있다.
    5. POLLOUT : 쓰기가 블록되지 않을 것이다.
    6. POLLWRNORM : 일반 쓰기 데이터가 블록되지 않을 것이다.
    7. POLLWRBAND : 우선권이 있는 데이터 쓰기가 블록되지 않을 것이다.
    8. POLLMSG : SIGPOLL 메시지가 사용 가능하다.

- revents
    1. POLLER : 주어진 파일 디스크립터에 에러가 있다.
    2. POOLHUP : 주어진 파일디스크립터에서 이벤트가 지체되고 있다.
    3. POLLNVAL : 주어진 파일 디스크립터가 유효하지 않다.

- 이 이벤트는 events 필드에서는 읨미가 없으며, 해당하는 경우에만 반환되는 값이므로 events에서 넘겨서도 안된다.

- POLLIN | POLLPRI 는 select에서의 읽기 이벤트와 동일하며
- POLLOUT | POLLWRBAND는 select에서의 쓰기 이벤트와 동일하다.

```c
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#define TIMEOUT  5 /* 타임아웃 초 */

int main(void) {
    struct pollfd fds[2];
    int ret;
    /* 표준 입력에 대한 이벤트 감시를 위한 준비 */
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    /* 표준 출력에 대한 이벤트 감시를 위한 준비 거의 항상 참이다. */
    fds[1].fd = STDOUT_FILENO;
    fds[1].events = POLLOUT;
    /* 준비 끝, 블록 시작 */
    ret = poll(fds, 2, TIMEOUT * 1000);
    if (ret == -1) {
        perror("poll");
        return 1;
    }

    if(!ret) {
        printf("%d seconds elapsed \n", TIMEOUT);
        return 0;
    }

    if (fds[0].revents & POLLIN)
        printf("stdin readable \n");
    if (fds[1].revents & POLLOUT)
        printf("stdout is writable \n");

        return 0;
}
```


- 다중 입출력이 의미 있을 때는? 
    - 하나의 스레드(메인이 되었든 서브 스레드가 되었든)에서
        - 여러 파일 디스크립터에 대해서 파일 입출력을 해야 할 때 필요한거다.
        - 예를들어 A,B,C,D 네개의 파일 디스크립터에 대해 읽고 쓰는 작업을 할건데,
        - A 작업을 하다가 (read) 블록이 되어버렸다.
        - 근디 B에서 데이터가 들어와서 읽을라고 하는데 A가 무한정 기다리는 경우가 생길 수 있다.
        - 그니까 하나의 스레드가 여러 파일에 대해서 읽고 쓰기 작업을 해야 할 때 필요한 것 !