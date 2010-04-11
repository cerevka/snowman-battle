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
    virtual void send(QByteArray message) const = 0;

    /**
     * Prijmuti dat v poli znaku.
     * @return prijate pole znaku
     */
    virtual QByteArray * recieve() = 0;
};

#endif // NETWORKINTERFACE_H
