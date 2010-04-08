#include "listenthread.h"

ListenThread::ListenThread(QTcpServer * serverSocket)
{
    this->serverSocket = serverSocket;

}

void ListenThread::run() {

}
