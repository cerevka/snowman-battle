#ifndef PLAYER_H
#define PLAYER_H

#include <QMutex>
#include <QTimerEvent>

#include "mapobject.h"

class Game;
class Weapon;

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
    bool interactPlayer(Player * const player);

    /**
     * Implementace abstraktní metody předka
     * @param shot zde nevyužit
     * @return vrací false (střela zabije hráče ale nepokračuje dále)
     */
    bool interactShot(Shot * const shot);

    /**
     * Obnoví hráče na náhodné lokaci
     */
    void respawn(void);

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

    /**
     * Tato metoda je zavolána pět vteřin poté, co byl hráč zabit, a způsobí, že se hráč znovu spawne
     * @param event časovač, který spustil tuto metodu
     */
    void timerEvent (QTimerEvent * const event);

    /**
     * Setr pro nastavení konkrétní zbraně jako aktuální (volá se po sebrání zbraně)
     * @param actualWeapon pořadí zbraně, na kterou se má přepnout
     */
    void setActualWeapon(const int actualWeapon);

    /**
     * Getr pro id
     */
    int getID(void) const;

    /**
     * Getr a setr pro směr hráče
     */
    Directions getDirection(void) const;
    void setDirection(const Directions direction);

    /**
     * Getr a setr pro příznak, zda se hráč pohybuje
     */
    bool isMoving(void) const;
    void setMoving(const bool moving);

    /**
     * Getr a setr pro příznak, zda hráč střílí
     */
    bool isShoting(void) const;
    void setShoting(const bool shoting);

    /**
     * Getr pro příznak, zda je hráč na mapě
     */
    bool isSpawned(void) const;

    /**
     * Getr a setr pro příznak aktivity
     */
    bool isActive(void) const;
    void setActive(const bool active);

    /**
     * Getr pro inventář zbraní
     */
    Weapon * const * getInventory(void) const;

    /**
     * Getr vracející ukaztel na hru, v rámci níž je tento hráč vytvořen
     */
    Game * getParentGame(void) const;

private:

    /**
     * Velikost hráče a kroku hráče
     */
    static double playerSize;
    static double stepSize;

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
     * Pokud je false, tak hráč nemůže vystřelit, protože mu běží cooldown
     */
    bool canShot;

    /**
     * Id timeru, který řídí respawn hráče
     */
    int idRespawnTimer;

    /**
     * Id timeru, který řídí cooldown zbraně
     */
    int idCooldownTimer;

    /**
     * Proměnná pro směr, příznak pohybu a příznak střelby
     */
    Directions direction;
    bool moving;
    bool shoting;

    /**
     * Pokud je true, tak je hráč na herní ploše
     */
    bool spawned;

    /**
     * Pokud hráč na síti neodpovídá, je označen jako neaktivní, tzn. tato proměnná bude false
     */
    bool active;

    /**
     * Zálohy souřadnice pro případ, že je potřeba hráče posunout zpět (na cílové místě je překážka)
     */
    double x1Backup;
    double x2Backup;
    double y1Backup;
    double y2Backup;

};

#endif // PLAYER_H
