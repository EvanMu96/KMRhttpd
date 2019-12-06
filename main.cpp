#include <iostream>
#include <sys/socket.h>
#include <sys/event.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <string>
#include <stdlib.h>

const int kReadEvent = 1;
const int kWriteEvent = 2;

inline void error_die(const char * sc)
{
    perror(sc);
    exit(1);
}

void updateEvents(int efd, int fd, int events, bool modify)
{
    struct kevent ev[2];
    int n = 0;
    if (events & kReadEvent) {
        EV_SET(&ev[n++], fd, EVFILT_READ, EV_ADD|EV_ENABLE, 0, 0, (void*)(intptr_t)fd);
    } else if (modify){
        EV_SET(&ev[n++], fd, EVFILT_READ, EV_DELETE, 0, 0, (void*)(intptr_t)fd);
    }
    if (events & kWriteEvent) {
        EV_SET(&ev[n++], fd, EVFILT_WRITE, EV_ADD|EV_ENABLE, 0, 0, (void*)(intptr_t)fd);
    } else if (modify){
        EV_SET(&ev[n++], fd, EVFILT_WRITE, EV_DELETE, 0, 0, (void*)(intptr_t)fd);
    }
    printf("%s fd %d events read %d write %d\n",
           modify ? "mod" : "add", fd, events & kReadEvent, events & kWriteEvent);
    int r = kevent(efd, ev, n, NULL, 0, NULL);
    error_die("kevent failed");
}



void setNonBlock(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if(flags < 0) error_die("fcntl failted");
    int r = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    if(r < 0) error_die("fcntl failed");
}



int main() {
    // initialization
    short port = 8000;
    int epollfd = kqueue();
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    memset (&addr, 0, sizeof(sockaddr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    int r = ::bind(listenfd, (struct sockaddr *) &addr, sizeof(struct sockaddr));
    printf("listen at %d \n", port);
    setNonBlock(listenfd);
    updateEvents(epollfd, listenfd, kReadEvent, false);

    return 0;
}