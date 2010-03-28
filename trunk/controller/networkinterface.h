#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <QObject>

/**
 * Definuje spolecne rozhrani pro clienta a server.
 */
class NetworkInterface : public QObject
{
public:
    NetworkInterface();

    /**
     * Odeslani dat v poli znaku.
     * @param message pole znaku k odeslani
     */
    virtual void send(char * message) const = 0;

    /**
     * Prijmuti dat v poli znaku.
     * @return prijate pole znaku
     */
    virtual char * recieve() const = 0;
};

#endif // NETWORKINTERFACE_H
