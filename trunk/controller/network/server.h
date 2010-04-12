#ifndef SERVER_H
#define SERVER_H


#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkProxy>
#include <QList>
#include "clientthread.h"
#include "networkinterface.h"
#include "globals.h"

/**
 * Server implementuje serverovou logiku. Je zapouzdren
 * pod vzorem Strategy pod jednotne rozhrani s NetworkInterface
 * a volani ji predava trida Network, ktera ho obsluhuje.
 */
class Server : public NetworkInterface
{
    Q_OBJECT
public:
    /**
     * Vytvoreni serveru naslouchajiciho na zvolenem portu.
     * @param port port, na kterem bude server naslouchat
     * @param count pocet hracu, kteri budou hrat
     */
    Server(int port, int count, NetworkInterface * const parent = 0);

    /**
     * Desktruktor uzavirajici serverovy socket.
     */
    virtual ~Server(void);

    /**
     * Odesilani dat v poli znaku.
     * @param message pole znaku k odeslani
     */
    void send(QByteArray * message);

    /**
     * Vrati ID server - vzdy 0.
     */
    int getNetworkID() const;

    /**
     * Nastavi ID serveru - nic nemeni, je pouze
     * kvuli jednotnemu pristupu pres Network.
     */
    void setNetworkID(int networkID);

private:
    /**
     * Uchovava ukazatel na serverovy socket, ke
     * kteremu se pripojuji klienti.
     */
    QTcpServer * serverSocket;


    /**
     * Udrzuje seznam otevrenych socketu s klienty.
     */
    QList<QTcpSocket*> clientsList;

    /**
     * Udrzuje seznam spustenych vlaken, ktera
     * ctou data od klientu.
     */
    QList<ClientThread*> clientThreadList;

    /**
     * Udrzuje informaci, kolik hracu se bude hry ucastnit.
     */
    int count;

signals:
    /**
     * Vyemituje zpravu, ze odeslal packet, aby ho i server
     * zpracoval.
     */
    void sentMessage(QByteArray * message);



private slots:
    void slotNewClient();


};

#endif // SERVER_H
