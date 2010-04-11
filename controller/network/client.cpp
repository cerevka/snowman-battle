#include "client.h"

Client::Client(QHostAddress address, int port, NetworkInterface *const parent):NetworkInterface(parent)
{
    // vytvori se TCP socket, kterym se pripoji k serveru
    clientSocket = new QTcpSocket(this);

    // pripojeni se k serveru
    clientSocket->connectToHost(address, port);

    #ifdef _DEBUG_
        qDebug() << "Network client: Connected to " << clientSocket->peerAddress() << "on port " << clientSocket->peerPort() << ".\n";
    #endif

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
QByteArray * Client::recieve() const
{
    return new QByteArray();

}
