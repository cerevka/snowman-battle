#ifndef PACKETPARSER_H
#define PACKETPARSER_H

#include <QObject>

class PacketParser : public QObject
{

Q_OBJECT

public:

    explicit PacketParser(QObject * const parent = 0);

    unsigned char * parse(unsigned char * const packet);


signals:

    /**
     * Signál přidělení id
     * @param id přidělené id
     */
    void idAssigned(int id);

    /**
     * Signál informující o tom, že danému id je přiděleno jméno (představovací paket)
     * @param id tomuto id se přidělí jméno
     * @param name ukazatel na jméno
     */
    void nameAssigned(int id, QString * name);

    /**
     * Signál výběru mapy (pro nás nezajímavé, protože máme jen jednu mapu)
     * @param mapID překvapivě id mapy
     */
    void mapChoosed(int mapID);

    /**
     * Signál startu hry
     */
    void gameStarted(void);

    /***************************************************/

    /**
     * Signál, že hráč stisknul klávesu pohybu nahoru
     * @param playerID id hráče, jenž klávesu stiskl
     */
    void norhtKeyPressed(int playerID);

    /**
     * Signál, že hráč stisknul klávesu pohybu doleva
     * @param playerID id hráče, jenž klávesu stiskl
     */
    void westKeyPressed(int playerID);

    /**
     * Signál, že hráč stisknul klávesu pohybu dolů
     * @param playerID id hráče, jenž klávesu stiskl
     */
    void southKeyPressed(int playerID);

    /**
     * Signál, že hráč stisknul klávesu pohybu doprava
     * @param playerID id hráče, jenž klávesu stiskl
     */
    void eastKeyPressed(int playerID);

    /**
     * Signál, že hráč stisknul klávesu střelby
     * @param playerID id hráče, jenž klávesu stiskl
     */
    void shotKeyPressed(int playerID);

    /**
     * Signál, že hráč stisknul klávesu změn zbraně
     * @param playerID id hráče, jenž klávesu stiskl
     */
    void changeKeyPressed(int playerID);

    /**
     * Signál, že hráč pustil klávesu pohybu
     * @param playerID id hráče, jenž klávesu pustil
     */
    void moveKeyReleased(int playerID);

    /**
     * Signál přijatého hello packetu
     * @param senderID id hráče, kteý paket poslal
     */
    void helloPacketAccepted(int senderID);

public slots:

};

#endif // PACKETPARSER_H
