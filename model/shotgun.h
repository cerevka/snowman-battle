#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "weapon.h"

/**
 * Třída reprezentující brokovnici
 * @author Ota Sandr
 */
class ShotGun : public Weapon
{

    Q_OBJECT

public:

    /**
     * Konstruktor vytvoří danému hráči brokovnice
     * @param parent hráč, kterému zbraň patří
     */
    inline explicit ShotGun(Player * const parent) :
            Weapon(parent) { this->ammo = 0; }

    /**
     * Implementace abstraktní metody předka (výstřel zbraně)
     */
    void shot(void);

    /**
     * Implementace abstraktní metody předka (doplnění nábojů)
     */
    inline void refill(void) { this->ammo = this->maxAmmo; }

private:

    /**
     * Maximum nábojů v brokovnici
     */
    static int maxAmmo;

    /**
     * Rychlost střely z brokovnice
     */
    static double shotSpeed;

    /**
     * Úhel rozptylu
     */
    static double spreadAngle;

};

#endif // SHOTGUN_H
