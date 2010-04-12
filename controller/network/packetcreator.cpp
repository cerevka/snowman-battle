
#include "../../globals.h"
#include "packetcreator.h"

PacketCreator::PacketCreator(QObject * const parent) :
    QObject(parent)
{

    gameEnginePacket = new QByteArray();
    sendingMutex = new QMutex();
    enginePacketMutex = new QMutex();

}

PacketCreator::~PacketCreator(void)
{

    delete gameEnginePacket;
    delete sendingMutex;
    delete enginePacketMutex;

}

/***********************************************************/

void PacketCreator::startGame(void)
{

    QByteArray * const packet = new QByteArray();

    packet->append(2); // délka
    packet->append(Globals::network->getNetworkID());
    packet->append(3); // typ start game

    sendPacket(packet);

}


/***********************************************************/
/* -------------------sloty pro klienty------------------- */

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

    QByteArray * const packet = new QByteArray();

    packet->append(2); // délka
    packet->append(Globals::network->getNetworkID());
    packet->append(11); // typ puštění klávesy

    sendPacket(packet);

}

void PacketCreator::sendHelloPacket(void)
{

    QByteArray * const packet = new QByteArray();

    packet->append(2); // délka
    packet->append(Globals::network->getNetworkID());
    packet->append(12); // typ hello paket

    sendPacket(packet);

}


/*********************************************************/
/* -------------sloty pro výstup enginu hry------------- */

void PacketCreator::sendGameEnginePacket(void)
{

    enginePacketMutex->lock();

    sendPacket(gameEnginePacket);
    gameEnginePacket->clear();

    enginePacketMutex->unlock();

}

void PacketCreator::spawnPlayer(int playerID, int x, int y, int direction)
{

    enginePacketMutex->lock();

    gameEnginePacket->append(8); // délka
    gameEnginePacket->append(Globals::network->getNetworkID());
    gameEnginePacket->append(20); // typ spawnutí hráče
    gameEnginePacket->append(playerID);
    gameEnginePacket->append(getFirstCharFromInt(x));
    gameEnginePacket->append(getSecondCharFromInt(x));
    gameEnginePacket->append(getFirstCharFromInt(y));
    gameEnginePacket->append(getSecondCharFromInt(y));
    gameEnginePacket->append(direction);

    enginePacketMutex->unlock();

}

void PacketCreator::spawnWeaponPack(int weaponPackID, int x, int y, int type)
{

    enginePacketMutex->lock();

    gameEnginePacket->append(8); // délka
    gameEnginePacket->append(Globals::network->getNetworkID());
    gameEnginePacket->append(21); // typ spawnutí zbraně
    gameEnginePacket->append(weaponPackID);
    gameEnginePacket->append(getFirstCharFromInt(x));
    gameEnginePacket->append(getSecondCharFromInt(x));
    gameEnginePacket->append(getFirstCharFromInt(y));
    gameEnginePacket->append(getSecondCharFromInt(y));
    gameEnginePacket->append(type);

    enginePacketMutex->unlock();

}

void PacketCreator::killPlayer(int playerID)
{

    enginePacketMutex->lock();

    gameEnginePacket->append(3); // délka
    gameEnginePacket->append(Globals::network->getNetworkID());
    gameEnginePacket->append(22); // typ zabití hráče
    gameEnginePacket->append(playerID);

    enginePacketMutex->unlock();

}

void PacketCreator::despawnWeaponPack(int weaponPackID)
{

    enginePacketMutex->lock();

    gameEnginePacket->append(3); // délka
    gameEnginePacket->append(Globals::network->getNetworkID());
    gameEnginePacket->append(23); // typ zmizení zbraně
    gameEnginePacket->append(weaponPackID);

    enginePacketMutex->unlock();

}

void PacketCreator::changeWeapon(int playerID, int weaponType, int restOfAmmo)
{

    enginePacketMutex->lock();

    gameEnginePacket->append(5); // délka
    gameEnginePacket->append(Globals::network->getNetworkID());
    gameEnginePacket->append(24); // typ změna zbraně
    gameEnginePacket->append(playerID);
    gameEnginePacket->append(weaponType);
    gameEnginePacket->append(restOfAmmo);

    enginePacketMutex->unlock();

}

void PacketCreator::createShot(int shotID, int x, int y)
{

    enginePacketMutex->lock();

    gameEnginePacket->append(7); // délka
    gameEnginePacket->append(Globals::network->getNetworkID());
    gameEnginePacket->append(25); // typ vytvoření střely
    gameEnginePacket->append(shotID);
    gameEnginePacket->append(getFirstCharFromInt(x));
    gameEnginePacket->append(getSecondCharFromInt(x));
    gameEnginePacket->append(getFirstCharFromInt(y));
    gameEnginePacket->append(getSecondCharFromInt(y));

    enginePacketMutex->unlock();

}

void PacketCreator::movePlayer(int playerID, int x, int y)
{

    enginePacketMutex->lock();

    gameEnginePacket->append(7); // délka
    gameEnginePacket->append(Globals::network->getNetworkID());
    gameEnginePacket->append(26); // typ posunutí hráče
    gameEnginePacket->append(playerID);
    gameEnginePacket->append(getFirstCharFromInt(x));
    gameEnginePacket->append(getSecondCharFromInt(x));
    gameEnginePacket->append(getFirstCharFromInt(y));
    gameEnginePacket->append(getSecondCharFromInt(y));

    enginePacketMutex->unlock();

}

void PacketCreator::moveShot(int shotID, int x, int y)
{

    enginePacketMutex->lock();

    gameEnginePacket->append(7); // délka
    gameEnginePacket->append(Globals::network->getNetworkID());
    gameEnginePacket->append(27); // typ posunutí střely
    gameEnginePacket->append(shotID);
    gameEnginePacket->append(getFirstCharFromInt(x));
    gameEnginePacket->append(getSecondCharFromInt(x));
    gameEnginePacket->append(getFirstCharFromInt(y));
    gameEnginePacket->append(getSecondCharFromInt(y));

    enginePacketMutex->unlock();

}

void PacketCreator::destroyShot(int shotID)
{

    enginePacketMutex->lock();

    gameEnginePacket->append(3); // délka
    gameEnginePacket->append(Globals::network->getNetworkID());
    gameEnginePacket->append(28); // typ zničení střely
    gameEnginePacket->append(shotID);

    enginePacketMutex->unlock();

}

void PacketCreator::playerShots(int playerID)
{

    enginePacketMutex->lock();

    gameEnginePacket->append(3); // délka
    gameEnginePacket->append(Globals::network->getNetworkID());
    gameEnginePacket->append(29); // typ zničení střely
    gameEnginePacket->append(playerID);

    enginePacketMutex->unlock();

}

/**********************************************************/
/* ------------------sloty pro řízení-------------------- */

void PacketCreator::quitGame(void)
{

    QByteArray * const packet = new QByteArray();

    packet->append(2); // délka
    packet->append(Globals::network->getNetworkID());
    packet->append(30); // typ ukončení hry

    sendPacket(packet);

}

void PacketCreator::pauseGame(void)
{

    QByteArray * const packet = new QByteArray();

    packet->append(2); // délka
    packet->append(Globals::network->getNetworkID());
    packet->append(31); // typ pauznutí hry

    sendPacket(packet);

}

void PacketCreator::activatePlayer(int playerID)
{

    QByteArray * const packet = new QByteArray();

    packet->append(3); // délka
    packet->append(Globals::network->getNetworkID());
    packet->append(32); // typ aktivování hráče
    packet->append(playerID);

    sendPacket(packet);


}

void PacketCreator::deactivatePlayer(int playerID)
{

    QByteArray * const packet = new QByteArray();

    packet->append(3); // délka
    packet->append(Globals::network->getNetworkID());
    packet->append(33); // typ deaktivování hráče
    packet->append(playerID);

    sendPacket(packet);


}

/**********************************************************/
/* -------------------sloty pro chat--------------------- */

void PacketCreator::sendChatMessage(int playerID, QString * msg)
{

    QByteArray * const packet = new QByteArray();

    int length = msg->length();
    int offset = 0; // udává, o kolik jsem se posunul vůči začátku řetězce


    // pokud je řetězec větší než jeden paket, tak ho musíme rozdělit
    while(length > 252){

        packet->append(255); // délka
        packet->append(Globals::network->getNetworkID());
        packet->append(40); // typ neukončená zpráva
        packet->append(playerID);

        for(int i = offset; i < 252; i++){
            packet->append(msg->at(i));
        }

        sendPacket(packet);
        packet->clear();

        offset += 252;
        length -= 252;

    }

    packet->append(length + 3); // délka
    packet->append(Globals::network->getNetworkID());
    packet->append(41); // typ ukončená zpráva
    packet->append(playerID);

    for(int i = offset; i < msg->length(); i++){
        packet->append(msg->at(i));
    }

    sendPacket(packet);

}

/*********************************************************/


void PacketCreator::sendKeyPress(const int typeOfKey)
{

    QByteArray * const packet = new QByteArray(4, '\0');

    packet->append(3);
    packet->append(Globals::network->getNetworkID());
    packet->append(10); // typ stisk klávesy
    packet->append(typeOfKey); // zadaná klávesa

    sendPacket(packet);

}

void PacketCreator::sendPacket(QByteArray * const packet)
{

    sendingMutex->lock();

    Globals::network->send(packet);

    sendingMutex->unlock();

}

unsigned char PacketCreator::getFirstCharFromInt(const int number)
{

    return (unsigned char)(number / 256);

}

unsigned char PacketCreator::getSecondCharFromInt(const int number)
{

    return (unsigned char)(number % 256);

}
