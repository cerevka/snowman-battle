#ifndef LISTENTHREAD_H
#define LISTENTHREAD_H

#include <QThread>

class ListenThread : public QThread
{
public:
    ListenThread();

    /**
     * Definuje cinnost naslouchajiciho vlakna.
     */
    void run();
};

#endif // LISTENTHREAD_H
