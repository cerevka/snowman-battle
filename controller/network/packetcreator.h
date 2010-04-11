#ifndef PACKETCREATOR_H
#define PACKETCREATOR_H

#include <QObject>

class PacketCreator : public QObject
{
Q_OBJECT
public:
    explicit PacketCreator(QObject *parent = 0);

signals:

public slots:

};

#endif // PACKETCREATOR_H
