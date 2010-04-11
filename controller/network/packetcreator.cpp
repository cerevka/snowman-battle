
#include "../../globals.h"
#include "packetcreator.h"

#include <QByteArray>

PacketCreator::PacketCreator(QObject * const parent) :
    QObject(parent)
{

}

void PacketCreator::startGame(void)
{

    QByteArray * const packet = new QByteArray(3, '\0');

    packet->data()[0] = 2;
    packet->data()[1] = 0; // TODO - tady bude něco jako getMyID
    packet->data()[2] = 3; // typ start game

    Globals::network->send(packet);

}

void PacketCreator::startMoveNorth(void)
{

    sendKeyPress(0);

}

void PacketCreator::startMoveWest(void)
{

    sendKeyPress(1);

}

void PacketCreator::startMoveSouth(void)
{

    sendKeyPress(2);

}

void PacketCreator::startMoveEast(void)
{

    sendKeyPress(3);

}

void PacketCreator::pressShot(void)
{

    sendKeyPress(4);

}

void PacketCreator::pressChangeWeapon(void)
{

    sendKeyPress(5);

}

void PacketCreator::stopMove(void)
{

    QByteArray * const packet =  new QByteArray(3, '\0');

    packet->data()[0] = 2;
    packet->data()[1] = 0; // TODO - tady bude něco jako getMyID
    packet->data()[2] = 11; // typ puštění klávesy

    Globals::network->send(packet);

}

void PacketCreator::sendHelloPacket(void)
{

    QByteArray * const packet = new QByteArray(3, '\0');

    packet->data()[0] = 2;
    packet->data()[1] = 0; // TODO - tady bude něco jako getMyID
    packet->data()[2] = 12; // typ hello paket

    Globals::network->send(packet);

}


void PacketCreator::sendKeyPress(const int typeOfKey)
{

    QByteArray * const packet = new QByteArray(4, '\0');

    packet->data()[0] = 3;
    packet->data()[1] = 0; // TODO - tady bude něco jako getMyID
    packet->data()[2] = 10; // typ stisk klávesy
    packet->data()[3] = typeOfKey; // klávesa nahoru

    Globals::network->send(packet);

}
