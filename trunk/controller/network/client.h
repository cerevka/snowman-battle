#ifndef CLIENT_H
#define CLIENT_H

#include "networkinterface.h";
#include <QTcpSocket>

/**
 * Client implementuje clientskou logiku. Je zapouzdren
 * pod vzorem Strategy pod jednotne rozhrani s NetworkInterface
 * a volani ji predava trida Network, ktera ho obsluhuje.
 */
class Client : NetworkInterface
{
public:
    /**
     * Vytvoreni klienta, ktery se pokusi pripojit na
     * zvolenou adresu a port.
     * @param address adresa, na ktere nasloucha server
     * @param port port, na kterem nasloucha server
     */
    Client(char * address, int port, NetworkInterface * const parent = 0);

    /**
     * Odeslani dat v poli znaku.
     * @param message pole dat k odeslani
     */
    virtual void send(char * message) const;

    /**
     * Prijmuti dat v poli znaku.
     * @return prijate pole dat
     */
    virtual char * recieve() const;

private:
    QTcpSocket * clientSocket;
};

#endif // CLIENT_H
