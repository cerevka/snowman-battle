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
    Client(QHostAddress address, int port, NetworkInterface * const parent = 0);

    /**
     * Destruktor uzavirajici socket
     */
    virtual ~Client(void);

    /**
     * Odeslani dat v poli znaku.
     * @param message pole dat k odeslani
     */
    void send(QByteArray message) const;

    /**
     * Prijmuti dat v poli znaku.
     * @return prijate pole dat
     */
    QByteArray * recieve() const;

private:
    QTcpSocket * clientSocket;
};

#endif // CLIENT_H
