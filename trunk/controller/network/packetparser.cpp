#include "packetparser.h"

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

void PacketParser::parseAll(QByteArray * const packets) {

    // Najdu si ukazatel na první znak
    unsigned char * pointer = (unsigned char *)packets->data();

    // Najdu si ukazatel, který mi ukazuje přesně o jedno místo za pole
    unsigned char * endOfArray = pointer + packets->size();

    // Dokud jsem nedojel nakonec tak parsuji paket po paketu
    while(pointer < endOfArray){

        pointer = parse(pointer);

    }

}

unsigned char * PacketParser::parse(unsigned char * const packet)
{

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

            if(length != 3){
                // TODO - chyba!!!
            }

            emit idAssigned(packet[3]);

            break;
        }

    // 1 - představovací packet (kombinace ID a jména) (OBA)
    case 1: {

            if(length < 3){
                // TODO - chyba!!!
            }

            QString * const name = new QString();

            for(int i = 4; i < (length + 1); i++){
                name->append(packet[i]);
            }

            emit nameAssigned(packet[3], name);

            break;
        }

    // 2 - informace o mapě (posílá pouze server klientům, jednorázová akce) (SERVER)
    case 2: {

            if(length != 3){
                // TODO - chyba!!!
            }

            emit mapChoosed(packet[3]);

            break;
        }

    // 3 - začátek hry (SERVER)
    case 3: {

            if(length != 2){
                // TODO - chyba!!!
            }

            emit gameStarted();

            break;
        }



    /* ----------------signály client -> server------------ */

    // 10 - stisk klávesy (typ klávesy) (CLIENT)
    case 10: {

            if(length != 3){
                // TODO - chyba!!!
            }

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

            default: {
                    // TODO - chyba!!!
                    break;
                }

            }

            break;
        }

    // 11 - puštění klávesy - pouze u šipek (CLIENT)
    case 11: {

            if(length != 2){
                // TODO - chyba!!!
            }

            emit moveKeyReleased(senderID);

            break;
        }

    // 12 - "Hello packet"
    case 12: {

            if(length != 2){
                // TODO - chyba!!!
            }

            emit helloPacketAccepted(senderID);

            break;
        }



    /* ----------------signály server->vsem------------- */

    // 20 - zjevení hráče IDp hráče na X,Y + směr
    case 20: {

            if(length != 8){
                // TODO - chyba!!!
            }

            emit playerSpawned(packet[3], convertBytesToInt(packet[4], packet[5]), convertBytesToInt(packet[6], packet[7]), packet[8]);

            break;
        }

    // 21 - zjevení zbraně IDg na X,Y + typ
    case 21: {

            if(length != 8){
                // TODO - chyba!!!
            }

            emit weaponPackSpawned(packet[3], convertBytesToInt(packet[4], packet[5]), convertBytesToInt(packet[6], packet[7]), packet[8]);

            break;
        }

    // 22 - zabití hráče IDp
    case 22: {

            if(length != 3){
                // TODO - chyba!!!
            }

            emit playerKilled(packet[3]);

            break;
        }

    // 23 - zmizení zbraně IDg
    case 23: {

            if(length != 3){
                // TODO - chyba!!!
            }

            emit weaponPackDespawned(packet[3]);

            break;
        }

    // 24 - výměna zbraně IDp, typ zbraně
    case 24: {

            if(length != 5){
                // TODO - chyba!!!
            }

            emit weaponChanged(packet[3], packet[4], packet[5]);

            break;
        }

    // 25 - vytvoření střely IDs, X, Y
    case 25: {

            if(length != 7){
                // TODO - chyba!!!
            }

            emit shotCreated(packet[3], convertBytesToInt(packet[4], packet[5]), convertBytesToInt(packet[6], packet[7]));

            break;
        }

    // 26 - přesun hráče IDp, X, Y
    case 26: {

            if(length != 7){
                // TODO - chyba!!!
            }

            emit playerMoved(packet[3], convertBytesToInt(packet[4], packet[5]), convertBytesToInt(packet[6], packet[7]));

            break;
        }

    // 27 - přesun střely IDs, X, Y
    case 27: {

            if(length != 7){
                // TODO - chyba!!!
            }

            emit shotMoved(packet[3], convertBytesToInt(packet[4], packet[5]), convertBytesToInt(packet[6], packet[7]));

            break;
        }

    // 28 - zničení střely IDs
    case 28: {

            if(length != 3){
                // TODO - chyba!!!
            }

            emit shotDestroyed(packet[3]);

            break;
        }



    /* ----------------řídící signály------------------------ */

    // 30 - konec hry
    case 30: {

            if(length != 2){
                // TODO - chyba!!!
            }

            emit gameQuited();

            break;
        }

    // 31 - pauza hry
    case 31: {

            if(length != 2){
                // TODO - chyba!!!
            }

            emit gamePaused();

            break;
        }



    /* -------------------chatové signály------------------ */

    // 40 - pokračující zpráva
    case 40: {

            if(length < 3){
                // TODO - chyba!!!
            }

            for(int i = 4; i < (length + 1); i++){
                messagesForChat.value(packet[3])->append(packet[i]);
            }

            break;

        }

    // 41 - ukončená zpráva
    case 41: {

            if(length < 3){
                // TODO - chyba!!!
            }

            // Vyberu správnou zprávu pro daného hráče ze seznamu
            QString * const message = messagesForChat.value(packet[3]);

            // A rozšířím jí o znaky v paketu
            for(int i = 4; i < (length + 1); i++){
                message->append(packet[i]);
            }

            // Vyšlu signál
            emit chatMessageRecieved(packet[3], message);

            // A svůj řetězec vynuluji
            message->clear();

            break;
        }



    // Chyba!!! (neznámý typ)
    default: {
            break;
        }

    }

    return (packet + length + 1);

}

int PacketParser::convertBytesToInt(unsigned char high, unsigned char low)
{

    return ( (high * 256) + low );

}
