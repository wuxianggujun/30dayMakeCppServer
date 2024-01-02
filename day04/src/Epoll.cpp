//
// Created by WuXiangGuJun on 2024/1/3.
//
#include "Epoll.hpp"
#include "util.hpp"
#include <unistd.h>
#include <cstring>

#define MAX_EVENTS 1000

Epoll::Epoll() : epfd(-1), events(nullptr){
    epfd = epoll_create1(0);
    errif(epfd == -1, "epoll create error");
    events = new epoll_event[MAX_EVENTS];
    bzero(events, sizeof(*events) * MAX_EVENTS);
}

Epoll::~Epoll() {
    if (epfd != -1) {
        close(epfd);
        epfd = -1;
    }
    delete[] events;
}

void Epoll::addFd(int fd, uint32_t op) {
    struct epoll_event event{};
    bzero(&event, sizeof(event));
    event.data.fd = fd;
    event.events = op;
    errif(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event) == -1, "epoll add event error");
}

std::vector<epoll_event> Epoll::poll(int timeout) {
    std::vector<epoll_event> activeEvents;
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, timeout);
    errif(nfds == -1, "epoll wait error");
    activeEvents.reserve(nfds);
    for (int idx = 0; idx < nfds; ++idx) {
        activeEvents.push_back(events[idx]);
    }
    return activeEvents;
}


