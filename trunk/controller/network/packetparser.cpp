
#include "packetparser.h"
#include "globals.h"

#include <QByteArray>

#ifdef _DEBUG_PACKET_PARSER_

#include <QDebug>

#endif

PacketParser::PacketParser(QObject * const parent) :
    QObject(parent)
{

    // Vytvářim textové řetězce pro chat pro jednotlivé hráče
    for(int i = 0; i < 6; i++){

        messagesForChat.append(new QString(""));

    }

}

PacketParser::~PacketParser(void)
{

    for(int i = 0; i < 6; i++){

        delete messagesForChat.value(i);

    }

}

void PacketParser::parseAll(QByteArray * packets) {

    #ifdef _DEBUG_PACKET_PARSER_
    qDebug() << "Packet parser: Start parsing all (lenght:" packets->size() << ")";
    #endif

    // Najdu si ukazatel na první znak
    unsigned char * pointer = (unsigned char *)packets->data();

    // Najdu si ukazatel, který mi ukazuje přesně o jedno místo za pole
    unsigned char * endOfArray = pointer + packets->size();

    // Dokud jsem nedojel nakonec, tak parsuji paket po paketu
    while(pointer < endOfArray){

        try {
            pointer = parse(pointer);
        } catch (QString & ex){
            #ifdef _DEBUG_
            qDebug() << "Packet parser: Exception in parsing (" << ex << ")";
            #endif
            return;
        }

    }

}

unsigned char * PacketParser::parse(unsigned char * const packet)
{
    #ifdef _DEBUG_PACKET_PARSER_
    qDebug() << "Packet parser: Start parsing a packet";
    #endif

    // Čtu první znak (délka paketu)
    unsigned char length = packet[0];

    // Pokud je paket dlouhý nula, tak dál nezpracovávám
    if(length == 0){
        return (packet + 1);
    }

    // Čtu druhý znak (id odesílatele)
    unsigned char senderID = packet[1];

    // Pokud je konec, tak zkončím
    if(length == 1){
        return (packet + 2);
    }

    // podle třetího znaku (typ paketu) se rozhodnu, jak dál
    switch(packet[2])
    {

    /* -----------------init------------------------- */

    // 0 - přidělení ID (SERVER)
    case 0: {

            testLenght(packet, 3, true);

            Globals::network->setNetworkID(packet[3]);

            #ifdef _DEBUG_PACKET_PARSER_
            qDebug() << "Packet parser: ID assigned";
            #endif

            break;
        }

    // 1 - představovací packet (kombinace ID a jména) (OBA)
    case 1: {

            testLenght(packet, 3, false);

            QString * const name = new QString();

            for(int i = 4; i < (length + 1); i++){
                name->append(packet[i]);
            }

            emit nameAssigned(packet[3], name);

            break;
        }

    // 2 - informace o mapě (posílá pouze server klientům, jednorázová akce) (SERVER)
    case 2: {

            testLenght(packet, 3, true);

            emit mapChoosed(packet[3]);

            break;
        }

    // 3 - začátek hry (SERVER)
    case 3: {

            testLenght(packet, 2, true);

            emit gameStarted();

            break;
        }



    /* ----------------signály client -> server------------ */

    // 10 - stisk klávesy (typ klávesy) (CLIENT)
    case 10: {

            testLenght(packet, 3, true);

            // podle typu klávesy pošlu signál
            switch(packet[3]){

            // nahoru
            case 0: {
                    emit norhtKeyPressed(senderID);
                    break;
                }

            // doleva
            case 1: {
                    emit westKeyPressed(senderID);
                    break;
                }

            // dolů
            case 2: {
                    emit southKeyPressed(senderID);
                    break;
                }

            // doprava
            case 3: {
                    emit eastKeyPressed(senderID);
                    break;
                }

            // výstřel
            case 4: {
                    emit shotKeyPressed(senderID);
                    break;
                }

            // změna zbraně
            case 5: {
                    emit changeKeyPressed(senderID);
                    break;
                }

            // pauza hry
            case 6: {
                    emit pauseKeyPressed();
                    break;
                }

            default: {
                    throw (QString("Type of key is unknown ") + QString(QString::number(packet[3])));
                    break;
                }

            }

            break;
        }

    // 11 - puštění klávesy - pouze u šipek (CLIENT)
    case 11: {

            testLenght(packet, 2, true);

            emit moveKeyReleased(senderID);

            break;
        }

    // 12 - "Hello packet"
    case 12: {

            testLenght(packet, 2, true);

            emit helloPacketAccepted(senderID);

            break;
        }



    /* ----------------signály server->vsem------------- */

    // 20 - zjevení hráče IDp hráče na X,Y + směr
    case 20: {

            testLenght(packet, 8, true);

            emit playerSpawned(packet[3], convertBytesToInt(packet[4], packet[5]), convertBytesToInt(packet[6], packet[7]), packet[8]);

            break;
        }

    // 21 - zjevení zbraně IDg na X,Y + typ
    case 21: {

            testLenght(packet, 8, true);

            emit weaponPackSpawned(packet[3], convertBytesToInt(packet[4], packet[5]), convertBytesToInt(packet[6], packet[7]), packet[8]);

            break;
        }

    // 22 - zabití hráče IDp
    case 22: {

            testLenght(packet, 3, true);

            emit playerKilled(packet[3]);

            break;
        }

    // 23 - zmizení zbraně IDg
    case 23: {

            testLenght(packet, 3, true);

            emit weaponPackDespawned(packet[3]);

            break;
        }

    // 24 - výměna zbraně IDp, typ zbraně, zbývající náboje
    case 24: {

            testLenght(packet, 5, true);

            emit weaponChanged(packet[3], packet[4], packet[5]);

            break;
        }

    // 25 - vytvoření střely IDs, X, Y
    case 25: {

            testLenght(packet, 7, true);

            emit shotCreated(packet[3], convertBytesToInt(packet[4], packet[5]), convertBytesToInt(packet[6], packet[7]));

            break;
        }

    // 26 - přesun hráče IDp, X, Y
    case 26: {

            testLenght(packet, 7, true);

            emit playerMoved(packet[3], convertBytesToInt(packet[4], packet[5]), convertBytesToInt(packet[6], packet[7]));

            break;
        }

    // 27 - přesun střely IDs, X, Y
    case 27: {

            testLenght(packet, 7, true);

            emit shotMoved(packet[3], convertBytesToInt(packet[4], packet[5]), convertBytesToInt(packet[6], packet[7]));

            break;
        }

    // 28 - zničení střely IDs
    case 28: {

            testLenght(packet, 3, true);

            emit shotDestroyed(packet[3]);

            break;
        }

    // 29 - výstřel hráče IDp
    case 29: {

            testLenght(packet, 3, true);

            emit playerShoted(packet[3]);

            break;
        }



    /* ----------------řídící signály------------------------ */

    // 30 - konec hry
    case 30: {

            testLenght(packet, 2, true);

            emit gameQuited();

            break;
        }

    // 31 - pauza hry
    case 31: {

            testLenght(packet, 2, true);

            emit gamePaused();

            break;
        }

    // 32 - pokračování ve hře
    case 32: {

            testLenght(packet, 2, true);

            emit gameResumed();

            break;

        }

    // 33 - aktivování hráče IDp
    case 33: {

            testLenght(packet, 3, true);

            emit playerActivated(packet[3]);

            break;
        }

    // 34 - deaktivování hráče IDp
    case 34: {

            testLenght(packet, 3, true);

            emit playerDeactivated(packet[3]);

            break;
        }

    // 35 - vítězství hráče IDp
    case 35: {

            testLenght(packet, 3, true);

            emit playerWon(packet[3]);

            break;

        }



    /* -------------------chatové signály------------------ */

    // 40 - pokračující zpráva
    case 40: {

            testLenght(packet, 3, false);

            for(int i = 4; i < (length + 1); i++){
                messagesForChat.value(packet[3])->append(packet[i]);
            }

            break;

        }

    // 41 - ukončená zpráva
    case 41: {

            testLenght(packet, 3, false);

            // Vyberu správnou zprávu pro daného hráče ze seznamu
            QString * const message = messagesForChat.value(packet[3]);

            // A rozšířím jí o znaky v paketu
            for(int i = 4; i < (length + 1); i++){
                message->append(packet[i]);
            }

            if((packet[1] != 0) ){

                QString copyOfMsg(*message);
                message->clear();

                Globals::packetCreator->sendChatMessage(packet[3], &copyOfMsg);
                break;
            } else {
                // Vyšlu signál
                emit chatMessageRecieved(packet[3], message);
            }

            // A svůj řetězec vynuluji
            message->clear();

            break;
        }

    // 50 - ikrementace skóre hráče IDp
    case 50: {

            testLenght(packet, 3, true);

            emit playersScoreIncremented(packet[3]);

            break;
        }

    case 51: {

            testLenght(packet, 4, true);

            emit playerTurned(packet[3], packet[4]);

            break;

        }

    // Chyba!!! (neznámý typ)
    default: {

            throw (QString("Unknown type: ") + QString(QString::number(packet[2])));

            break;
        }

    }

    return (packet + length + 1);

}

inline int PacketParser::convertBytesToInt(unsigned char high, unsigned char low)
{

    return ( (high * 256) + low );

}

inline void PacketParser::testLenght(unsigned char * const packet, const int expectedLength, const bool equal)
{

    if(equal){
        if(packet[0] != expectedLength){
            throw (QString("Packet has incorrect length, type: ") + QString(QString::number(packet[2])));
        }
    } else {
        if(packet[0] < expectedLength){
            throw (QString("Packet is too short, type: ") + QString(QString::number(packet[2])));
        }
    }

}
