#ifndef LISTENTHREAD_H
#define LISTENTHREAD_H

#include <QThread>
#include <QTcpServer>


class ListenThread : public QThread
{
public:
    /**
     * Vytvori nove naslouchajici vlakno.
     * @param serverSocket
     */
    ListenThread(QTcpServer * serverSocket);

    /**
     * Definuje cinnost naslouchajiciho vlakna.
     */
    void run();
private:
    QTcpServer * serverSocket;
};


#endif // LISTENTHREAD_H
