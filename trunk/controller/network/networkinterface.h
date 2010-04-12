#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <QObject>
#include <QHostAddress>
#include <QByteArray>

#ifdef _DEBUG_
#include <QtDebug>
#endif

/**
 * Definuje spolecne rozhrani pro clienta a server.
 */
class NetworkInterface : public QObject
{

    Q_OBJECT

public:
    NetworkInterface(QObject * parent = 0);

    ~NetworkInterface();

    /**
     * Odeslani dat v poli znaku.
     * @param message pole znaku k odeslani
     */
    virtual void send(QByteArray * message) = 0;

    /**
     * Vrati hodnotu ID v siti.
     */
    virtual int getNetworkID() const = 0;

    /**
     * Nastavi ID v siti.
     */
    virtual void setNetworkID(int networkID) = 0;
};

#endif // NETWORKINTERFACE_H
