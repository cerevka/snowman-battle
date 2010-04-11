#include "network.h"


Network::~Network()
{

}

void Network::send(QByteArray message) const
{
    network->send(message);
}

QByteArray * Network::recieve() {
    return network->recieve();
}

