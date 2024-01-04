//
// Created by WuXiangGuJun on 2024/1/5.
//

#include <Connection.hpp>
#include <Socket.hpp>
#include <iostream>

int main() {
    Socket *sock = new Socket();
    sock->Connect("127.0.0.1", 1234);

    Connection *conn = new Connection(nullptr, sock);

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