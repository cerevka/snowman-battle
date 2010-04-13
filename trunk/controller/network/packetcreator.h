#ifndef PACKETCREATOR_H
#define PACKETCREATOR_H

#include <QObject>
#include <QByteArray>
#include <QMutex>

/**
 * Třída, která slouží k vytváření paketů a jejich posílání po síti
 */
class PacketCreator : public QObject
{

    Q_OBJECT

public:

    /**
     * Konstruktor slouží k vytvoření "vytvářeče" paketů
     * @param parent objekt, který je rodičem
     */
    explicit PacketCreator(QObject * const parent = 0);

    ~PacketCreator(void);

public slots:

    /* ------------------------init------------------------- */

    // TODO tyhle sloty si ještě musím promylset

    /**
     * Slot pro přidělení packetu
     * @param id id, které se stanici přidělí
     */
    QByteArray * assignID(int id);
//
//    /**
//     * Slot představovacího paketu
//     * @param id id, kterému se přidělí jméno
//     * @param name ukazatel na jméno
//     */
//    void assignName(int id, QString * name);
//
    /**
     * Slot pro výběr mapy (pro nás nezajímavé, protože máme jen jednu mapu)
     * @param mapID překvapivě id mapy
     */
    void chooseMap(int mapID);

    /**
     * Slot startu hry
     */
    void startGame(void);


    /***********************************************************/
    /* -------------------sloty pro klienty------------------- */

    /**
     * Slot, do kterého se posílá, že hráč stisknul klávesu pro pohyb nahoru
     */
    void startMoveNorth(void);

    /**
     * Slot, do kterého se posílá, že hráč stisknul klávesu pro pohyb doleva
     */
    void startMoveWest(void);

    /**
     * Slot, do kterého se posílá, že hráč stisknul klávesu pro pohyb dolů
     */
    void startMoveSouth(void);

    /**
     * Slot, do kterého se posílá, že hráč stisknul klávesu pro pohyb doprava
     */
    void startMoveEast(void);

    /**
     * Slot, do kterého se posílá, že hráč stisknul klávesu pro střelbu
     */
    void pressShot(void);

    /**
     * Slot, do kterého se posílá, že hráč stisknul klávesu pro změnu zbraně
     */
    void pressChangeWeapon(void);

    /**
     * Slot, do kterého se posílá, že hráč pustil klávesu pro pohyb
     */
    void stopMove(void);

    /**
     * Slot pro odeslání hello paketu
     */
    void sendHelloPacket(void);

    /*********************************************************/
    /* -------------sloty pro výstup enginu hry------------- */

    /**
     * Slot, do kterého se posílá informace o tom, že je možné odeslat paket enginu hry
     */
    void sendGameEnginePacket(void);

    /**
     * Slot, do kterého se posílá informace o naspawnování hráče
     * @param playerID id hráče, který se má spawnout
     * @param x x-ová souřadnice místa spawnutí (levý horní roh)
     * @param y y-ová souřadnice místa spawnutí (levý horní roh)
     * @param direction směr, kterým bude hráč otočený
     */
    void spawnPlayer(int playerID, int x, int y, int direction);

    /**
     * Slot, do kterého se posílá informace o objevení zbraně na herní ploše
     * @param weaponPackID id zbraně, která se objeví
     * @param x x-ová souřadnice místa objevení (levý horní roh)
     * @param y y-ová souřadnice místa objevení (levý horní roh)
     * @param type typ zbraně, která se objeví
     */
    void spawnWeaponPack(int weaponPackID, int x, int y, int type);

    /**
     * Slot, do kterého se posílá informace o zabití hráče
     * @param playerID id hráče, který byl zabit
     */
    void killPlayer(int playerID);

    /**
     * Slot, do kterého se posílá informace o zmizení zbraně
     * @param weaponPackID id zbraně, která zmizí
     */
    void despawnWeaponPack(int weaponPackID);

    /**
     * Slot, do kterého se posílá informace o změny zbraně
     * @param playerID id hráče, který si mění zbraň
     * @param weaponType typ zbraně, kterou si bere
     * @param restOfAmmo počet zbývajících nábojů v této zbrani
     */
    void changeWeapon(int playerID, int weaponType, int restOfAmmo);

    /**
     * Slot, do kterého se posílá informace o vytvoření střely
     * @param shotID, id této střely
     * @param x x-ová souřadnice střely (její střed)
     * @param y y-ová souřadnice střely (její střed)
     */
    void createShot(int shotID, int x, int y);

    /**
     * Slot, do kterého se posílá informace o pohybu hráče
     * @param playerID id hráče, který se bude přesouvat
     * @param x x-ová souřadnice místa, kam se má hráč přesunout (levý horní roh)
     * @param y y-ová souřadnice místa, kam se má hráč přesunout (levý horní roh)
     */
    void movePlayer(int playerID, int x, int y);

    /**
     * Slot, do kterého se posílá informace o pohybu střely
     * @param shotID id střely, který se bude přesouvat
     * @param x x-ová souřadnice místa, kam se má střela přesunout (její střed)
     * @param y y-ová souřadnice místa, kam se má střela přesunout (její střed)
     */
    void moveShot(int shotID, int x, int y);

    /**
     * Slot, do kterého se posílá informace o zničení střely
     * @param shotID id střely, který se má zničit
     */
    void destroyShot(int shotID);

    /**
     * Slot, do kterého se posílá informace o výstřelu hráče
     * @param playerID id hráče, který střílí
     */
    void playerShots(int playerID);

    /**
     * Slot, do kterého se posílá informace o zvýšení skóre hráče
     * @param playerID id hráče, kterému se zvýšilo skóre
     */
    void incrementScore(int playerID);

    /**********************************************************/
    /* ------------------sloty pro řízení-------------------- */

    /**
     * Slot pro ukončení hry
     */
    void quitGame(void);

    /**
     * Slot pro zapauzování hry
     */
    void pauseGame(void);

    /**
     * Slot pro aktivování hráče
     * @param playerID id hráče, který se má aktivovat
     */
    void activatePlayer(int playerID);

    /**
     * Slot pro aktivování hráče
     * @param playerID id hráče, který se má deaktivovat
     */
    void deactivatePlayer(int playerID);

    /**********************************************************/
    /* -------------------sloty pro chat--------------------- */

    /**
     * Slot, kterým se odesílá chatová zpráva
     * @param playerID id hráče, jenž posílá zprávu
     * @param msg ukazatel na zprávu, která se odešle
     */
    void sendChatMessage(int playerID, QString * msg);


private:

    /**
     * Do tohoto pole ukládají informace z enginu hry a na konci každého framu se odešle
     */
    QByteArray * gameEnginePacket;

    /**
     * Tento mutex slouží k zamykání odesílání paketů (aby s e odesílaly za sebou)
     */
    QMutex * sendingMutex;

    /**
     * Tento mutex je k zamykání
     */
    QMutex * enginePacketMutex;

    /**
     * Pomocná metoda odešla paket typu stisknutá kláves
     * @param typeOfkey číslo klávesy, které se bude posílat v paketu
     */
    void sendKeyPress(const int typeOfKey);

    /**
     * Pomocná metoda pro vytváření 3-bytových paketů
     * @param typeOfPacket číslo typu paketu
     */
    void createThreeBytesPacket(const int typeOfPacket);

    /**
     * Tato metoda slouží k odeslání paketu (přiodesílání zamkne odesílací mutex)
     * @param packet data k odeslání
     */
    void sendPacket(QByteArray * const packet);

    unsigned char getFirstCharFromInt(const int number);
    unsigned char getSecondCharFromInt(const int number);

};

#endif // PACKETCREATOR_H
