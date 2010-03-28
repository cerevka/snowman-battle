#ifndef PLAYER_H
#define PLAYER_H

#include "mapobject.h"

class Game;

/**
 * Výčtový typ pro směr hráče
 */
enum Directions
{
    NORTH, WEST, SOUTH, EAST
};

class Player : public MapObject
{

public:

    /**
     * Vytvoření nového hráče (pouze na začátku hry)
     * @param parent hra, v rámci níž je hráč vytvořen
     */
    explicit Player(Game * const parent = 0);

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
     * Getr a setr pro směr hráče
     */
    Directions getDirection(void) const;
    void setDirection(const Directions direction);

    /**
     * Getr a setr příznak, zda se hráč pohybuje
     */
    bool isMoving(void) const;
    void setMoving(const bool moving);

    /**
     * Getr pro příznak, zda je hráč na mapě
     */
    bool isSpawned(void) const;

private:

    /**
     * Proměnné pro směr a příznak pohybu
     */
    Directions direction;
    bool moving;

    /**
     * Pokud je true, tak je hráč na herní ploše
     */
    bool spawned;

    /**
     * Zálohy souřadnice pro případ, že je potřeba hráče posunout zpět (na cílové místě je překážka)
     */
    double x1Backup;
    double x2Backup;
    double y1Backup;
    double y2Backup;

};

#endif // PLAYER_H
