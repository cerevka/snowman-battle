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

     // Inicializuji se pocatecni casy v seznamu hello packetu, aby se pak mohli jen replacova
      for (int i=0; i<6; ++i) {
          lastHelloList.append(QTime::QTime());
      }


    // propoji se signal noveho spojeni s jeho obsluhou
    QObject::connect(serverSocket, SIGNAL(newConnection()), this, SLOT(slotNewClient()));
    // propoji se signal o odeslani packetu s parserem
    QObject::connect(this, SIGNAL(sentMessage(QByteArray*)), Globals::packetParser, SLOT(parseAll(QByteArray*)));
    // propoji se informace o novem hello packetu
    QObject::connect(Globals::packetParser, SIGNAL(helloPacketAccepted(int)), this, SLOT(slotIncommingHelloPacket(int)));
    // propoji se signal o lagujicim klientovy
    QObject::connect(this, SIGNAL(clientLags(int)), Globals::gameFacade, SLOT(deactivatePlayer(int)));
    QObject::connect(this, SIGNAL(clientIsBack(int)), Globals::gameFacade, SLOT(activatePlayer(int)));

    Globals::network = new Network(this);

    // spusti se kontrola hello packetu
    startTimer(550);
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


void Server::send(QByteArray * message)
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

void Server::timerEvent(QTimerEvent *event)
{
    //qDebug() << "Zahajena kontrola hello packetu.";
    // podiva se na vsechny klienty a porovna jejich casy
    // od nuly mi stejne nikdy nic neprijde
    for (int i = 1; i < Globals::players + 1; ++i) {
        // podivam se na prodlevu klientu
        if (lastHelloList.at(i).msecsTo(QTime::currentTime()) > 600) {
            // pokud je prodleva moc velka, podivam se, jestli jiz neni lagly
            if  (laggingClientsList.indexOf(i) == -1) {
                // klient jeste neni lagly, deaktivuji ho

                // nejaky klient se moc zpozdil
                qDebug() << "Klient cislo " << i << " laguje.";
                // vyemituji signal
                emit clientLags(i);

                // oznacim si hrace, ze je v lagu
                laggingClientsList.append(i);
            }
        } else {
            // prodleva klienta je naprosto v norme, podivam se, zda neni mezi laglymi
            if (laggingClientsList.indexOf(i) != -1) {
                // klient se nachazi v laglistu
                emit clientIsBack(i);
                // odstranim ho ze seznamu laglych klientu
                laggingClientsList.removeAt(laggingClientsList.indexOf(i));

                qDebug() << "Klient je opet spravne pripojen.";
            }
        }



       // qDebug() << "Prodleva pro " << i << " je " <<(lastHelloList.at(i).msecsTo(QTime::currentTime()));
    }
}


void Server::slotNewClient()
{
    if (Globals::isGameRunning == false)
    {
      // ziska se socket, pomoci ktereho se bude komunikovat s klientam
      QTcpSocket * clientSocket = serverSocket->nextPendingConnection();
      // prida se ukazatel na klientsky socket do seznamu
      clientsList << clientSocket;
      // vytvori se nove klientske vlakno
      ClientThread * thread = new ClientThread(clientSocket);

      // napoji se signal, ze byla prijata zprava, na parser
      QObject::connect(thread, SIGNAL(newMessage(QByteArray*)), Globals::packetParser, SLOT(parseAll(QByteArray*)));


      clientSocket->write(*Globals::packetCreator->assignID(clientsList.size()));

      // a spusti se
      thread->start();

      // schova se ukazatel na vlakno
      clientThreadList << thread;

      #ifdef _DEBUG_
        qDebug() << "Network Server: Client has been connected.\n";
      #endif
    } else {
        QTcpSocket * clientSocket = serverSocket->nextPendingConnection();
        clientSocket->disconnectFromHost();
        #ifdef _DEBUG_
         qDebug() << "Network Server: Client has been refused.";
        #endif

     }

}

void Server::slotIncommingHelloPacket(int id)
{
    // Updatuju si cas posledniho hello packetu pro daneho klienta
    lastHelloList.replace(id, QTime::currentTime());
    // qDebug() << "Obdrzel jsem hello packet od " << id << " v " << lastHelloList.at(id);
}

