#include "packetparser.h"

PacketParser::PacketParser(QObject * const parent) :
    QObject(parent)
{
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

    // 20 - zjevení hráče na X,Y + IDp hráče
    case 20: {
            break;
        }

    // 21 - zjevení zbraně IDg na X,Y + typ
    case 21: {
            break;
        }

    // 22 - zabití hráče IDp
    case 22: {
            break;
        }

    // 23 - zmizení zbraně IDg
    case 23: {
            break;
        }

    // 24 - výměna zbraně IDp, typ zbraně
    case 24: {
            break;
        }

    // 25 - vytvoření střely IDs, X, Y, směr
    case 25: {
            break;
        }

    // 26 - začátek pohybu hráče IDp, směr
    case 26: {
            break;
        }

    // 27 - konec pohybu hráče IDp
    case 27: {
            break;
        }

    // 28 - zničení střely IDs
    case 28: {
            break;
        }



    /* ----------------řídící signály------------------------ */

    // 30 - konec hry
    case 30: {
            break;
        }

    // 31 - pauza hry
    case 31: {
            break;
        }



    /* -------------------chatové signály------------------ */

    // 40 - pokračující zpráva
    case 40: {
            break;
        }

    // 41 - ukončená zpráva
    case 41: {
            break;
        }



    // Chyba!!! (neznámý typ)
    default: {
            break;
        }

    }

}
