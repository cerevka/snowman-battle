#ifndef SERVER_H
#define SERVER_H

#include "networkinterface.h"
#include <QTcpServer>
#include <QNetworkProxy>

/**
 * Server implementuje serverovou logiku. Je zapouzdren
 * pod vzorem Strategy pod jednotne rozhrani s NetworkInterface
 * a volani ji predava trida Network, ktera ho obsluhuje.
 */
class Server : public NetworkInterface
{
public:
    /**
     * Vytvoreni serveru naslouchajiciho na zvolenem portu.
     * @param port port, na kterem bude server naslouchat
     */
    Server(int port, NetworkInterface * const parent = 0);

    /**
     * Odesilani dat v poli znaku.
     * @param message pole znaku k odeslani
     */
    virtual void send(QByteArray message) const;

    /**
     * Prijimani dat v poli znaku.
     * @return prijate pole znaku
     */
    virtual QByteArray recieve();


private:

    QTcpServer * serverSocket;


};

#endif // SERVER_H
