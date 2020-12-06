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