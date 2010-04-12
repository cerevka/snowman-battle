#include "network.h"


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
