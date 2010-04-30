#ifndef PLAYER_H
#define PLAYER_H

#include "mapobject.h"

class Game;
class Weapon;
class GameTimer;

/**
 * Výčtový typ pro směr hráče
 */
enum Directions
{
    NORTH, WEST, SOUTH, EAST
};

/**
 * Tato třída reprezentuje hráče v herní logice
 */
class Player : public MapObject
{

    Q_OBJECT

public:

    /**
     * Vytvoření nového hráče (pouze na začátku hry)
     * @param parent hra, v rámci níž je hráč vytvořen
     */
    Player(Game * const parent, const int id);

    /**
     * Implementace abstraktní metody předka
     * @param player zde nevyužit
     * @return vrací false (hráč nemůže vstoupit na jiného hráče)
     */
    inline bool interactPlayer(Player * const) { return false; }

    /**
     * Implementace abstraktní metody předka
     * @param shot ten, komu patří střela, si připíše bod
     * @return vrací false (střela zabije hráče, ale nepokračuje dále)
     */
    bool interactShot(Shot * const shot);

    /**
     * Tato metoda posune hráčovy souřadnice, aby se mohly zjistit kolize
     */
    void tryMove(void);

    /**
     * Pokud se hráč na dané místo nemůže přesunout kvůli kolizi, tak jej tato metoda vrátí zpět
     */
    void backMove(void);

    /**
     * Po zavolání této metody hráč vytřelí aktuální zbraní
     */
    void shot(void);

    /**
     * Změní aktuální zbraň hráče na další, která má náboje
     */
    void changeWeapon(void);

    /***************************************************/

    /**
     * Setr pro nastavení konkrétní zbraně jako aktuální (volá se po sebrání zbraně)
     * @param actualWeapon pořadí zbraně, na kterou se má přepnout
     */
    void setActualWeapon(const int actualWeapon);

    /**
     * Metoda pro zvýšení skóre
     */
    void incrementScore(void);

    /**
     * Getr pro id
     * @return id tohoto hráče
     */
    inline int getID(void) const { return this->playerID; }

    /**
     * Getr pro směr hráče
     * @return směr, kterým je hráč otočený
     */
    inline Directions getDirection(void) const { return this->direction; }

    /**
     * Setr pro směr hráče
     * @param direction směr, který se má nastavit
     */
    void setDirection(const Directions direction);

    /**
     * Getr pro příznak, zda se hráč pohybuje
     * @return je-li true, pak se hráč pohybuje
     */
    inline bool isMoving(void) const { return this->moving; }

    /**
     * Setr pro příznak, zda se hráč pohybuje
     * @param pokud je true, hráč se začne pohybovat
     */
    inline void setMoving(const bool moving) { this->moving = moving; }

    /**
     * Getr pro příznak, zda hráč bude střílet
     * @return pokud je true, tak hráč v příštím frame vystřelí
     */
    inline bool isShoting(void) const { return this->shoting; }

    /**
     * Setr pro příznak, zda hráč bude střílet
     * @param shoting pokud je true, tak hráč v příštím frame vystřelí
     */
    inline void setShoting(const bool shoting) { this->shoting = shoting; }

    /**
     * Getr pro příznak, zda je hráč na mapě
     * @return true pokud je hráč spawnut
     */
    inline bool isSpawned(void) const { return this->spawned; }

    /**
     * Getr pro příznak aktivity
     * @return true pokud je hráč aktivovaný
     */
    inline bool isActive(void) const { return this->active; }

    /**
     * Setr pro příznak aktivity
     * @param active pokud je true, tak hráč bude aktivován
     */
    void setActive(const bool active);

    /**
     * Getr pro inventář zbraní
     * @return ukazatel na inventář zbraní
     */
    inline Weapon * const * getInventory(void) const { return this->inventory; }

    /**
     * Getr vracející ukaztel na hru, v rámci níž je tento hráč vytvořen
     * @return ukazatel na hru, kterou tento hráč hraje
     */
    inline Game * getParentGame(void) const { return this->parentGame; }


public slots:

    /**
     * Obnoví hráče na náhodné lokaci
     */
    void respawn(void);

    /**
     * Zajistí, že hráč může střílet
     */
    void enableShooting(void);


signals:

    /**
     * Signál spawnutí hráče
     * @param playerID id spawnutého hráče
     * @param x nová x-ová souřadnice hráče (levý horní roh)
     * @param y nová y-ová souřadnice hráče (levý horní roh)
     * @param direction směr, kterým je hráč otočený
     */
    void playerSpawned(int playerID, int x, int y, int direction);

    /**
     * Signál otočení hráče
     * @param playerID id hráče, který se otočil
     * @param direction nový směr, kterým je hráč otočený
     */
    void playerTurned(int playerID, int direction);

    /**
     * Signál výstřelu hráče
     * @param playerID id hráče, který vystřelil
     */
    void playerShoted(int playerID);

    /**
     * Signál změny zbraně
     * @param playerID id hráče, který změnil zbraň
     * @param weapon zbraň, kterou si vzal
     * @param restOfAmmo zbývající náboje ve zbrani
     */
    void weaponChanged(int playerID, int weapon, int restOfAmmo);

    /**
     * Signál zabití hráče
     * @param playerID id hráče, který byl zabit
     */
    void playerKilled(int playerID);

    /***************************************************/

    /**
     * Signál zvýšení skóre
     * @param playerID id hráče, kterému se skóre zvýšilo
     */
    void scoreIncremented(int playerID);

    /**
     * Signál vítězství hráče
     * @param playerID id hráče, který zvítězil
     */
    void playerWon(int playerID);

    /***************************************************/

    /**
     * Signál aktivování hráče
     * @param playerID id hráče, který byl aktivován
     */
    void playerActivated(int playerID);

    /**
     * Signál deaktivování hráče
     * @param playerID id hráče, který byl deaktivován
     */
    void playerDeactivated(int playerID);

private:

    /**
     * Velikost hráče v pixelech
     */
    static double playerSize;

    /**
     * Velikost kroku hráče
     */
    static double stepSize;

    /**
     * Doba respawnu hráče ve framech
     */
    static int respawnTimeFrames;

    /**
     * Prodeleva mezi dvěma výstřely zbraně
     */
    static int cooldownTimeFrames;

    /***************************************************/

    /**
     * Seznam zbraní hráče
     */
    Weapon * inventory[3];

    /**
     * Pořadí zbraně, kterou hráč právě používá, v inventáři
     */
    int actualWeapon;

    /**
     * Jednoznačný idetifikátor hráče (pořadí v allPlayer)
     */
    int playerID;

    /**
     * Počet kolikrát daný hráč zabil soupeře
     */
    int score;

    /**
     * Pokud je false, tak hráč nemůže vystřelit, protože mu běží cooldown
     */
    bool canShot;

    /**
     * Časovač, který řídí respawn hráče
     */
    GameTimer * respawnTimer;

    /**
     * Časovač, který řídí cooldown zbraně
     */
    GameTimer * cooldownTimer;

    /**
     * Proměnná pro směr
     */
    Directions direction;

    /**
     * Proměnná pro příznak pohybu
     */
    bool moving;

    /**
     * Proměnná pro příznak střelby
     */
    bool shoting;

    /**
     * Pokud je true, tak je hráč na herní ploše
     */
    bool spawned;

    /**
     * Pokud hráč na síti neodpovídá, je označen jako neaktivní, tzn. tato proměnná bude false
     */
    bool active;

    /***************************************************/

    /**
     * Záloha x-ové souřadnice (levého horního rohu) pro případ, že je potřeba hráče posunout zpět (na cílovém místě je překážka)
     */
    double x1Backup;

    /**
     * Záloha y-ové souřadnice (levého horního rohu) pro případ, že je potřeba hráče posunout zpět (na cílovém místě je překážka)
     */
    double x2Backup;

    /**
     * Záloha x-ové souřadnice (pravého spodního rohu) pro případ, že je potřeba hráče posunout zpět (na cílovém místě je překážka)
     */
    double y1Backup;

    /**
     * Záloha y-ové souřadnice (pravého spodního rohu) pro případ, že je potřeba hráče posunout zpět (na cílovém místě je překážka)
     */
    double y2Backup;

};

#endif // PLAYER_H
