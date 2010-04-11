#ifndef CLIENT_H
#define CLIENT_H


#include <QTcpSocket>
#include "networkinterface.h";
#include "clientthread.h"

/**
 * Client implementuje clientskou logiku. Je zapouzdren
 * pod vzorem Strategy pod jednotne rozhrani s NetworkInterface
 * a volani ji predava trida Network, ktera ho obsluhuje.
 */
class Client : NetworkInterface
{
    Q_OBJECT
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
    void send(const QByteArray * message) const;

private:
    /**
     * Udrzuje si ukazatel na socket, kterym komunikuje
     * se serverem.
     */
    QTcpSocket * clientSocket;

private slots:
    /**
     * Informuje o uspesnem pripojeni k serveru.
     */
    void slotConnected();
};

#endif // CLIENT_H
