//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once

#include "Macros.hpp"

#include <functional>

class EventLoop;

class Socket;

class Channel;

class Buffer;

class Connection {
public:
    enum State {
        Invalid = 1,
        Handshaking,
        Connected,
        Closed,
        Failed
    };

private:
    EventLoop *loop_;
    Socket *sock_;
    Channel *channel_{nullptr};
    State state_{State::Invalid};

    Buffer *read_Buffer_{nullptr};
    Buffer *send_Buffer_{nullptr};
    std::function<void(Socket *)> delete_Connection_Callback;
    std::function<void(Connection *)> on_connect_callback_;

    void ReadNonBlocking();
    void WriteNonBlocking();
    void ReadBlocking();
    void WriteBlocking();

public:
    Connection(EventLoop *loop,Socket *sock);
    ~Connection();

    DISALLOW_COPY_AND_MOVE(Connection);

    void Read();
    void Write();

    void SetDeleteConnectionCallback(std::function<void(Socket *)> const&callback);
    void SetOnConnectCallback(std::function<void(Connection *)> const&callback);
    State GetState();
    void Close();
    void SetSendBuffer(const char* str);
    Buffer *GetReadBuffer();
    const char* ReadBuffer();
    Buffer *GetSendBuffer();
    const char* SendBuffer();
    void GetLineSendBuffer();
    Socket* GetSocket();

    void OnConnect(std::function<void()> fn);
};

