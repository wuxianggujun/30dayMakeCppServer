#include "Server.hpp"
#include <iostream>
#include "Buffer.hpp"
#include "Connection.hpp"
#include "EventLoop.hpp"
#include "Socket.hpp"

int main() {
    auto *loop = new EventLoop();
    auto *server = new Server(loop);
    server->OnConnect([](Connection *conn) {
        conn->Read();
        if (conn->GetState() == Connection::State::Closed) {
            conn->Close();
            return;
        }
        std::cout << "Message from client " << conn->GetSocket()->GetFd() << ": " << conn->ReadBuffer() << std::endl;
        conn->SetSendBuffer(conn->ReadBuffer());
        conn->Write();
    });

    loop->Loop();
    delete server;
    delete loop;
    return 0;
}