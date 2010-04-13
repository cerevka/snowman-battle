#ifndef PACKETPARSER_H
#define PACKETPARSER_H

#include <QObject>
#include <QByteArray>

/**
 * Tato třída slouží pro parsování paketů přicházejících ze sítě
 */
class PacketParser : public QObject
{

Q_OBJECT

public:

    /**
     * Konstrutor vytvoří parser
     * @param parent objekt, který je rodičem
     */
    explicit PacketParser(QObject * const parent = 0);

    /**
     * Destruktor zruší parser
     */
    ~PacketParser(void);

public slots:

    /**
     * Zpracuje všechny pakety v zadanám poli bytů
     * @param packets pole bytů, které se má naparsovat
     */
    void parseAll(QByteArray * packets);

signals:

    /* ------------------------init------------------------- */

//    /**
//     * Signál přidělení id
//     * @param id přidělené id
//     */
//    void idAssigned(int id);

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

    /***********************************************************/
    /* ----------------signály client -> server--------------- */

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

    /*********************************************************/
    /* ----------------signály server->všem----------------- */

    /**
     * Signál naspawnování hráče
     * @param playerID id hráče, který se má spawnout
     * @param x x-ová souřadnice místa spawnutí (levý horní roh)
     * @param y y-ová souřadnice místa spawnutí (levý horní roh)
     * @param direction směr, kterým bude hráč otočený
     */
    void playerSpawned(int playerID, int x, int y, int direction);

    /**
     * Signál objevení zbraně na herní ploše
     * @param weaponPackID id zbraně, která se objeví
     * @param x x-ová souřadnice místa objevení (levý horní roh)
     * @param y y-ová souřadnice místa objevení (levý horní roh)
     * @param type typ zbraně, která se objeví
     */
    void weaponPackSpawned(int weaponPackID, int x, int y, int type);

    /**
     * Signál zabití hráče
     * @param playerID id hráče, který byl zabit
     */
    void playerKilled(int playerID);

    /**
     * Signál zmizení zbraně
     * @param weaponPackID id zbraně, která zmizí
     */
    void weaponPackDespawned(int weaponPackID);

    /**
     * Signál změny zbraně
     * @param playerID id hráče, který si mění zbraň
     * @param weaponType typ zbraně, kterou si bere
     * @param restOfAmmo počet zbývajících nábojů v této zbrani
     */
    void weaponChanged(int playerID, int weaponType, int restOfAmmo);

    /**
     * Signál vytvoření střely
     * @param shotID, id této střely
     * @param x x-ová souřadnice střely (její střed)
     * @param y y-ová souřadnice střely (její střed)
     */
    void shotCreated(int shotID, int x, int y);

    /**
     * Signál pohybu hráče
     * @param playerID id hráče, který se bude přesouvat
     * @param x x-ová souřadnice místa, kam se má hráč přesunout (levý horní roh)
     * @param y y-ová souřadnice místa, kam se má hráč přesunout (levý horní roh)
     */
    void playerMoved(int playerID, int x, int y);

    /**
     * Signál pohybu střely
     * @param shotID id střely, který se bude přesouvat
     * @param x x-ová souřadnice místa, kam se má střela přesunout (její střed)
     * @param y y-ová souřadnice místa, kam se má střela přesunout (její střed)
     */
    void shotMoved(int shotID, int x, int y);

    /**
     * Signál zničení střely
     * @param shotID id střely, který se má zničit
     */
    void shotDestroyed(int shotID);

    /**
     * Signál výstřelu hráče (pro odečtení nábojů)
     * @param playerID id hráče, který vystřelil
     */
    void playerShoted(int playerID);

    /**
     * Signál zvýšení skóre hráče
     * @param playerID id hráče, kterému se zvýšilo skóre
     */
    void playersScoreIncremented(int playerID);

    /**********************************************************/
    /* -------------------řídící signály--------------------- */

    /**
     * Signál ukončení hry
     */
    void gameQuited(void);

    /**
     * Signál zapauzování hry
     */
    void gamePaused(void);

    /**
     * Signál aktivování hráče
     * @param playerID id hráče, který se má aktivovat
     */
    void playerActivated(int playerID);

    /**
     * Signál deaktivování hráče
     * @param playerID id hráče, který se má deaktivovat
     */
    void playerDeactivated(int playerID);

    /**********************************************************/
    /* -------------------chatové signály-------------------- */

    /**
     * Signál přijetí chatové zprávy
     * @param playerID id hráče, jenž poslal zprávu
     * @param msg ukazatel na zprávu, která přišla
     */
    void chatMessageRecieved(int playerID, QString * msg);

private:

    /**
     * Seznam textových řetězců pro kompletování zpráv
     */
    QList<QString *> messagesForChat;

    /**
     * Pomocná metoda která naparsuje jeden paket a vrátí ukazatel na začátek dalšího
     * @param packet ukazatel na první znak packetu
     * @return ukzatatel naprvní znak dalšího packetu
     */
    unsigned char * parse(unsigned char * const packet);

    /**
     * Pomocná metoda která zkonvertuje dvojici unsigned charů na int
     * @param high bity reprezentující vyšší řád čísla
     * @param low bity reprezentující nižší řád čísla
     * @return číslo které reprezentovaly dva vstupní znaky
     */
    int convertBytesToInt(const unsigned char high, const unsigned char low);

    /**
     * Pomocná metoda, která se používá pro zjištění správnosti délky paketu
     * @param ukazatel na začátek paketu
     * @param expectedLength očekávaná nebo minimální délka paketu
     * @param equal pokud je true tak je zadaná délka očekávaná, pokud false tak minimální
     */
    void testLenght(unsigned char * const packet, const int expectedLength, const bool equal);

};

#endif // PACKETPARSER_H
