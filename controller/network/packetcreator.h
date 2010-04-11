#ifndef PACKETCREATOR_H
#define PACKETCREATOR_H

#include <QObject>

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

public slots:

    /* ------------------------init------------------------- */

    // TODO tyhle sloty si ještě musím promylset

//    /**
//     * Slot pro přidělení packetu
//     * @param id id, které se stanici přidělí
//     */
//    void assignID(int id);
//
//    /**
//     * Slot představovacího paketu
//     * @param id id, kterému se přidělí jméno
//     * @param name ukazatel na jméno
//     */
//    void assignName(int id, QString * name);
//
//    /**
//     * Slot pro výběr mapy (pro nás nezajímavé, protože máme jen jednu mapu)
//     * @param mapID překvapivě id mapy
//     */
//    void chooseMap(int mapID);

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

private:

    /**
     * Pomocná metoda odešla paket typu stisknutá kláves
     * @param typeOfkey číslo klávesy, které se bude posílat v paketu
     */
    void sendKeyPress(const int typeOfKey);

};

#endif // PACKETCREATOR_H
