#include "client.h"

Client::Client(QHostAddress address, int port, NetworkInterface *const parent):NetworkInterface(parent)
{
    // vytvori se TCP socket, kterym se pripoji k serveru
    clientSocket = new QTcpSocket(this);

    // napojeni signalu o uspesnem pripojeni
    QObject::connect(clientSocket, SIGNAL(connected()), this, SLOT(slotConnected()));

    // pripojeni se k serveru
    clientSocket->connectToHost(address, port);

}

Client::~Client(void)
{
      clientSocket->close();
}

void Client::send(const QByteArray * message) const
{
    if (clientSocket->write(*message) == -1) {
        #ifdef _DEBUG_
            qDebug() << "Network Client: Write error into socket.";
        #endif
    }

}

void Client::slotConnected()
{
    // spojeni bylo navazano, spusti se vlakno, ktere
    // bude cist data ze serveru
    ClientThread * thread = new ClientThread(clientSocket);
    thread->start();


    #ifdef _DEBUG_
        qDebug() << "Network Client: Connected to the address " << clientSocket->peerAddress().toString() << "on the port " << clientSocket->peerPort() << ".\n";
    #endif
}
