#include "server.h"

Server::Server(int port, int count, NetworkInterface *const parent) : NetworkInterface(parent)
{
    // ulozi si pocet hracu
    this->count = count;

    // vytvori se QListy
    /*
    clientsList = new QList<QTcpSocket*>();
    clientThreadList =  QList<QThread*>();*/

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
    QObject::connect(serverSocket, SIGNAL(newConnection()), this, SLOT(slotNewClient()));
    // propoji se signal o odeslani packetu s parserem
    QObject::connect(this, SIGNAL(sentMessage(const QByteArray*const)), Globals::packetParser, SLOT(parseAll(QByteArray*const)));
}


Server::~Server(void){
    // ukonci vsechna vlakna, se kterymi komunikuje
    // kazde vlakno pak pri svem niceni uzavre prislusny socket
    for (int i = 0; i < clientThreadList.size(); ++i) {
        clientThreadList.at(i)->quit();
    }

    // nakonec se uzavre poslouchajici socket
    serverSocket->close();
}


void Server::send(const QByteArray * message) const
{

    // server rozesle zpravu vsem klientum
    for (int i = 0; i < clientsList.size(); ++i) {
        clientsList.at(i)->write(*message);
    }

    // vyemituje zpravu o odeslanem signalu, aby se zpracovala
    // take serverem
    emit sentMessage(message);


}

int Server::getNetworkID() const
{
    // pro server vzdy nula, kvuli jednotnemu pristupu
    return 0;
}

void Server::setNetworkID(int networkID)
{
    // nic nedela, server je vzdy 0
    // kvuli jednotnemu pristupu z Network
}


void Server::slotNewClient()
{
    qDebug() << "Pred prvnim pozitim.";
    //if ((!clientsList.isEmpty()) && (clientsList.size()<this->count))
    //{
      // ziska se socket, pomoci ktereho se bude komunikovat s klientam
      QTcpSocket * clientSocket = serverSocket->nextPendingConnection();
      // prida se ukazatel na klientsky socket do seznamu
      clientsList << clientSocket;
      // vytvori se nove klientske vlakno
      ClientThread * thread = new ClientThread(clientSocket);

      // napoji se signal, ze byla prijata zprava, na parser
      QObject::connect(thread, SIGNAL(newMessage(QByteArray* const)), Globals::packetParser, SLOT(parseAll(QByteArray*const)));

      clientSocket->write(*Globals::packetCreator->assignID(clientsList.size()));

      // a spusti se
      thread->start();

      // schova se ukazatel na vlakno
      clientThreadList << thread;

      #ifdef _DEBUG_
        qDebug() << "Network Server: Client has been connected.\n";
      #endif
//    } else {
//        QTcpSocket * clientSocket = serverSocket->nextPendingConnection();
//        clientSocket->disconnectFromHost();
//        #ifdef _DEBUG_
//         qDebug() << "Network Server: Client has been refused.";
//        #endif
//
//    }
    qDebug() << "Po poziti.";

}
