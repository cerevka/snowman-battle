#include "network.h"

Network::Network(NetworkInterface *strategy, QObject *const parent)
{
    network = strategy;
    QObject::connect(Globals::packetParser, SIGNAL(nameAssigned(int,QString*)), this, SLOT(slotAddName(int,QString*)));
}

Network::~Network()
{

}

void Network::send(QByteArray * message)
{
    network->send(message);
}

int Network::getNetworkID() const
{
    return network->getNetworkID();
}

void Network::setNetworkID(int networkID)
{
    network->setNetworkID(networkID);
}

void Network::slotAddName(int id, QString *name)
{
    Globals::mainWindow->addName(id, new QString(*name));
    qDebug() << "Zaregisroval jsem zadost o jmeno: " << *name << " od " << id;
}
