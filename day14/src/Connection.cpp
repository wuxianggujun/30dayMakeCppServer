//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "Connection.hpp"
#include "Socket.hpp"
#include "Channel.hpp"
#include "Buffer.hpp"
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <utility>
#include <cassert>
#include "util.hpp"


Connection::Connection(EventLoop *loop, Socket *sock) : loop_(loop), sock_(sock) {

    if (loop_ != nullptr) {
        channel_ = new Channel(loop_, sock_->GetFd());
        channel_->EnableRead();
        channel_->UseET();
    }

    read_Buffer_ = new Buffer();
    send_Buffer_ = new Buffer();
    state_ = State::Connected;
}

Connection::~Connection() {
    if (loop_ != nullptr) {
        delete channel_;
    }

    delete sock_;
    delete read_Buffer_;
    delete send_Buffer_;
}

void Connection::Read() {
    ASSERT(state_ == State::Connected, "connection state is disconnected!");
    read_Buffer_->Clear();
    if (sock_->IsNonBlocking()) {
        ReadNonBlocking();
    } else {
        ReadBlocking();
    }
}

void Connection::Write() {
    ASSERT(state_ == State::Connected, "connection state is disconnected!");
    if (sock_->IsNonBlocking()) {
        WriteNonBlocking();
    } else {
        WriteBlocking();
    }
    send_Buffer_->Clear();
}

void Connection::ReadNonBlocking() {
    int sockfd = sock_->GetFd();
    char buf[1024];  // 这个buf大小无所谓
    while (true) {   // 使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
        memset(buf, 0, sizeof(buf));
        ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
        if (bytes_read > 0) {
            read_Buffer_->Append(buf, bytes_read);
        } else if (bytes_read == -1 && errno == EINTR) {  // 程序正常中断、继续读取
            printf("continue reading\n");
            continue;
        } else if (bytes_read == -1 &&
                   ((errno == EAGAIN) || (errno == EWOULDBLOCK))) {  // 非阻塞IO，这个条件表示数据全部读取完毕
            break;
        } else if (bytes_read == 0) {  // EOF，客户端断开连接
            printf("read EOF, client fd %d disconnected\n", sockfd);
            state_ = State::Closed;
            break;
        } else {
            printf("Other error on client fd %d\n", sockfd);
            state_ = State::Closed;
            break;
        }
    }
}

void Connection::WriteNonBlocking() {
    int sockfd = sock_->GetFd();
    char buf[send_Buffer_->Size()];
    memcpy(buf, send_Buffer_->ToStr(), send_Buffer_->Size());
    int data_size = send_Buffer_->Size();
    int data_left = data_size;
    while (data_left > 0) {
        ssize_t bytes_write = write(sockfd, buf + data_size - data_left, data_left);
        if (bytes_write == -1 && errno == EINTR) {
            printf("continue writing\n");
            continue;
        }
        if (bytes_write == -1 && errno == EAGAIN) {
            break;
        }
        if (bytes_write == -1) {
            printf("Other error on client fd %d\n", sockfd);
            state_ = State::Closed;
            break;
        }
        data_left -= bytes_write;
    }
}

/**
 * @brief Never used by server, only for client
 *
 */
void Connection::ReadBlocking() {
    int sockfd = sock_->GetFd();
    unsigned int rcv_size = 0;
    socklen_t len = sizeof(rcv_size);
    getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcv_size, &len);
    char buf[rcv_size];
    ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
    if (bytes_read > 0) {
        read_Buffer_->Append(buf, bytes_read);
    } else if (bytes_read == 0) {
        printf("read EOF, blocking client fd %d disconnected\n", sockfd);
        state_ = State::Closed;
    } else if (bytes_read == -1) {
        printf("Other error on blocking client fd %d\n", sockfd);
        state_ = State::Closed;
    }
}

/**
 * @brief Never used by server, only for client
 *
 */
void Connection::WriteBlocking() {
    // 没有处理send_buffer_数据大于TCP写缓冲区，的情况，可能会有bug
    int sockfd = sock_->GetFd();
    ssize_t bytes_write = write(sockfd, send_Buffer_->ToStr(), send_Buffer_->Size());
    if (bytes_write == -1) {
        printf("Other error on blocking client fd %d\n", sockfd);
        state_ = State::Closed;
    }
}

void Connection::Close() { delete_Connection_Callback(sock_); }

Connection::State Connection::GetState() { return state_; }

void Connection::SetSendBuffer(const char *str) { send_Buffer_->SetBuf(str); }

Buffer *Connection::GetReadBuffer() { return read_Buffer_; }

const char *Connection::ReadBuffer() { return read_Buffer_->ToStr(); }

Buffer *Connection::GetSendBuffer() { return send_Buffer_; }

const char *Connection::SendBuffer() { return send_Buffer_->ToStr(); }

void Connection::SetDeleteConnectionCallback(std::function<void(Socket *)> const &callback) {
    delete_Connection_Callback = callback;
}

void Connection::SetOnConnectCallback(std::function<void(Connection *)> const &callback) {
    on_connect_callback_ = callback;
    channel_->SetReadCallback([this]() { on_connect_callback_(this); });
}

void Connection::GetLineSendBuffer() { send_Buffer_->GetLine(); }

Socket *Connection::GetSocket() { return sock_; }