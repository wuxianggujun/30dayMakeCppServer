//
// Created by WuXiangGuJun on 2024/1/3.
//
#include <iostream>
#include "Connection.hpp"
#include "Socket.hpp"

int main() {
    auto *sock = new Socket();
    sock->Connect("127.0.0.1", 1234);

    auto *conn = new Connection(nullptr, sock);

    while (true) {
        conn->GetLineSendBuffer();
        conn->Write();
        if (conn->GetState() == Connection::State::Closed) {
            conn->Close();
            break;
        }
        conn->Read();
        std::cout << "Message from server: " << conn->ReadBuffer() << std::endl;
    }

    delete conn;
    return 0;
}