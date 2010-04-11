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

/**
 * Metoda implementujici odesilani klienta.
 */
void Client::send(QByteArray message) const
{

}

/**
 * Metoda implemenutujici prijimani dat klientem.
 */
QByteArray * Client::recieve()
{
    return new QByteArray();

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
