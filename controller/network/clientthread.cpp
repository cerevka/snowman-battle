#include "clientthread.h"

ClientThread::ClientThread(QTcpSocket * socket)
{
    this->socket = socket;
}

void ClientThread::run() {
    while (socket->canReadLine()) {
        // precte vsechny dostupne byty se socketu
        message = socket->readAll();
        // nyni je treba data vyemitovat na slot, kde je prijme parser


    }

}
