#ifndef CLIENT_H
#define CLIENT_H


#include <QTcpSocket>
#include "networkinterface.h"
#include "clientthread.h"
#include "globals.h"

/**
 * Client implementuje clientskou logiku. Je zapouzdren
 * pod vzorem Strategy pod jednotne rozhrani s NetworkInterface
 * a volani ji predava trida Network, ktera ho obsluhuje.
 */
class Client : public NetworkInterface
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
    void send(QByteArray * message);

    /**
     * Vrati ID v siti, ktera mu byla pridelena klientem.
     */
    int getNetworkID() const;

    /**
     * Nastavi klientovi jeho networkID
     * @param networkID pridelovane ID
     */
    void setNetworkID(int networkID);

private:
    /**
     * Udrzuje si ukazatel na socket, kterym komunikuje
     * se serverem.
     */
    QTcpSocket * clientSocket;

    /**
     * Udrzuje ukazatel na naslouchajici vlakno
     */
    ClientThread * clientThread;

    /**
     * Uchovava ID v siti.
     */
    int networkID;

private slots:
    /**
     * Informuje o uspesnem pripojeni k serveru.
     */
    void slotConnected();

    /**
     * Informuje o odpojeni od serveru.
     */
    void slotDisconnected();

    /**
     * Informuje o chybe pripojeni.
     */
    void slotErrorConnect();
};

#endif // CLIENT_H
