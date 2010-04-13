#include "client.h"

Client::Client(QHostAddress address, int port, QString name, NetworkInterface *const parent):NetworkInterface(parent)
{
    // vytvori se TCP socket, kterym se pripoji k serveru
    clientSocket = new QTcpSocket(this);

    // ulozi si jmeno
    this->name = name;

    // napojeni signalu o uspesnem pripojeni
    QObject::connect(clientSocket, SIGNAL(connected()), this, SLOT(slotConnected()));
    // napojeni signalu o odpojeni
    QObject::connect(clientSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    // napojeni signalu o chybe spojeni
    QObject::connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotErrorConnect()));

    // pripojeni se k serveru
    clientSocket->connectToHost(address, port);

    // zapouzdreni do Network
    Globals::network = new Network(this);


}

Client::~Client(void)
{
    // ukonci naslouchaji vlakno, ktere pri svem zaniku
    // uzavre komunikacni socket
    clientThread->quit();
}

void Client::send(QByteArray * message)
{
    if (clientSocket->write(*message) == -1) {
        #ifdef _DEBUG_
            qDebug() << "Network Client: Write error into socket.";
        #endif
    }

}

int Client::getNetworkID() const
{
    return networkID;
}

void Client::setNetworkID(int networkID)
{
    this->networkID = networkID;    

    // v odpovedi odesle packet se svym jmenem
    Globals::packetCreator->assignName(networkID, &this->name);
}

void Client::slotConnected()
{
    // spojeni bylo navazano, spusti se vlakno, ktere
    // bude cist data ze serveru
    clientThread = new ClientThread(clientSocket);

    // napoji se na parser
    QObject::connect(clientThread, SIGNAL(newMessage(QByteArray*)), Globals::packetParser, SLOT(parseAll(QByteArray*)));

    clientThread->start();


    #ifdef _DEBUG_
        qDebug() << "Network Client: Connected to the address " << clientSocket->peerAddress().toString() << "on the port " << clientSocket->peerPort() << ".";
    #endif
}

void Client::slotDisconnected()
{
    #ifdef _DEBUG_
        qDebug() << "Network Client: Disconnected.";
    #endif
}

void Client::slotErrorConnect()
{
    #ifdef _DEBUG_
        qDebug() << "Network Client: Connect error.";
    #endif
}
