#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QTcpSocket>
//#include "globals.h"

#ifdef _DEBUG_
#include <QtDebug>
#endif

/**
 * Vytvori vlakno, ktere bude poslouchat nova prichozi data.
 * Server: Vytvari pro kazdeho klienta zvlastni vlakno.
 * Client: Vytvori si po pripojeni prave jedno vlakno, kde
 * bude prijimat data od serveru.
 */
class ClientThread : public QThread
{
    Q_OBJECT
public:
    /**
     * Vytvori vlakno komunikujici s danym socketem.
     * @param socket komunikacni socket klienta
     */
    ClientThread(QTcpSocket * socket);

    /**
     * Definuje ukonceni vlakna.
     */
    ~ClientThread();

    /**
     * Definuje cinnost vlakna - pouze spusti smycku udalosti
     * a dale jiz reaguje jen na signaly.
     */
    void run();

private:
    /**
     * Ukazatel na socket, ktery umoznuje komunikaci s klientem.
     */
    QTcpSocket * socket;

    /**
     * Pole prijatych dat.
     */
    QByteArray * message;

    /**
     * Uchovava informaci o delce prichoziho packetu.
     */
    int length;

signals:
    /**
     * Tento signal je vyemitovan vzdy, kdy jsou prijata
     * nova data a predava je ke zpracovani.
     * @param message pole prijatych dat
     */
    void newMessage(QByteArray * message);

private slots:
    /**
     * Tento slot je informovan vzdy, kdy jsou na socketu
     * nova data, ktera je treba precist.
     */
    void incomingMessage();

};

#endif // CLIENTTHREAD_H
