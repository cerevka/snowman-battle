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
//    length = this->socket->read(1).at(0);
//
//    // prectu vsechny znaky patrici k prichozimu packetu
//    QByteArray message = socket->read(length);

    // precte se vsechno, co prislo a nestaram se o obsah
    QByteArray message = socket->readAll();

//     qDebug() << "Velikost: " << message.size() << " ukazatel: " << &message;

//     printMessage(&message);

//    // vyemituji signal nove prichozi zpravy
    emit newMessage(&message);


}

void ClientThread::printMessage(QByteArray * message)
{
    qDebug() << "New message: ";
    for (int i = 0; i < message->size(); ++i) {
        qDebug() << (int) message->at(i);
    }
}
