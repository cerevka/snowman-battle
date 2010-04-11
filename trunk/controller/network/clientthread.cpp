#include "clientthread.h"

ClientThread::ClientThread(QTcpSocket * socket)
{
    this->socket = socket;

    // vlakno se napoji na signal
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(incomingMessage()));
}

ClientThread::~ClientThread(){
    // pri zanikani vlakna se uzavre socket
    socket->disconnectFromHost();
}

void ClientThread::run()
{
    // spusti se smycka udalosti
    exec();

}

void ClientThread::incomingMessage()
{
    // dostal jsem zpravu, ze je co cist
    // prectu prvni bajt (delka prichozi informace)
    // na nulte pozici
    length = this->socket->read(1).at(0);

    // prectu vsechny znaky patrici k prichozimu packetu
    message = socket->read(length);

    // vyemituji signal nove prichozi zpravy
    emit newMessage(message);

    #ifdef _DEBUG_
    qDebug() << "Network Client Thread: New message";
    #endif
}
