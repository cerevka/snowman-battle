#include "server.h"

Server::Server(int port, NetworkInterface *const parent) : NetworkInterface(parent)
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
          qDebug() << "Network Server: Server is ready on port " << serverSocket->serverPort() << ".";
      }
    #endif

    // propoji se signal noveho spojeni s jeho obsluhou
      QObject::connect(serverSocket, SIGNAL(newConnection()), this, SLOT(slotNewClient(QTcpSocket)));
}

/**
 * Imlementuje uzavreni socketu.
 */
Server::~Server(void){
    serverSocket->close();
}

/**
 * Metoda implementujici odesilani serveru.
 */
void Server::send(QByteArray message) const
{

}

/**
 * Metoda implemenutujici prijimani dat serverem.
 */
QByteArray * Server::recieve()
{
    return new QByteArray();
}

void Server::slotNewClient()
{
    // ziska se socket, pomoci ktereho se bude komunikovat s klientam
    QTcpSocket * clientSocket = serverSocket->nextPendingConnection();
    // prida se ukazatel na klientsky socket do seznamu
    clientsList << clientSocket;
    // vytvori se nove klientske vlakno a spusti se
    ClientThread(clientSocket).start();

}
