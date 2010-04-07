#include "server.h"

Server::Server(int port, NetworkInterface *const parent)
{
    serverSocket = new QTcpServer(this);
    // zakaze se pouziti proxy
    serverSocket->setProxy(QNetworkProxy::NoProxy);
    // nastavi se maximalni pocet spojeni - pro sest hracu staci pet klientu
    serverSocket->setMaxPendingConnections(5);

    // nastavi se port pro naslouchani
    bool listening = serverSocket->listen(QHostAddress::Any, port);


    #ifdef _DEBUG_
      if (listening) {
        qDebug() << "Server is ready on port " << port << ".";
      }
    #endif

}

/**
 * Metoda implementujici odesilani serveru.
 */
void Server::send(char *message) const
{

}

/**
 * Metoda implemenutujici prijimani dat serverem.
 */
char * Server::recieve()
{

}
