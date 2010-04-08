#include "clientthread.h"

ClientThread::ClientThread(QTcpSocket * socket)
{
    this->socket = socket;
}

void ClientThread::run() {

}
