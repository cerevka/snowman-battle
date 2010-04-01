#include "network.h"


void Network::send(char * message) const
{
    network->send(message);
}

char * Network::recieve() {
    return network->recieve();
}
