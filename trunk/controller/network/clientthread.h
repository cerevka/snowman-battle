#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QByteArray>

class ClientThread : public QThread
{
public:
    /**
     * Vytvori vlakno, ktere bude komunikovat s danym klientem.
     */
    ClientThread(QTcpSocket * socket);

    /**
     * Definuje cinnost vlakna - stala cteci smycka.
     */
    void run();

private:
    QTcpSocket * socket;

signals:
    QByteArray newMessage();
};

#endif // CLIENTTHREAD_H
