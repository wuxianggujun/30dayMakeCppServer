//
// Created by WuXiangGuJun on 2024/1/3.
//

class Epoll;

class Channel;

class EventLoop {

private:
    Epoll *epoll;
    bool quit;

public:
    EventLoop();

    ~EventLoop();

    void loop();

    void updateChannel(Channel *channel);
};
