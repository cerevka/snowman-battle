#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "weapon.h"

/**
 * Třída reprezentující brokovnici
 */
class ShotGun : public Weapon
{

public:

    /**
     * Konstruktor vytvoří danému hráči brokovnice
     * @param parent hráč, kterému zbraň patří
     */
    explicit ShotGun(Player * const parent);

    /**
     * Implementace abstraktní metody předka (výstřel zbraně)
     */
    void shot(void);

    /**
     * Implementace abstraktní metody předka (doplnění nábojů)
     */
    void refill(void);

};

#endif // SHOTGUN_H
