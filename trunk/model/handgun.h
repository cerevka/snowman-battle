#ifndef HANDGUN_H
#define HANDGUN_H

#include "weapon.h"

/**
 * Tato třída reprezentuje pistoli, kterou každý hráč používá jako základní zbraň
 * @author Ota Sandr
 */
class HandGun : public Weapon
{

    Q_OBJECT

public:

    /**
     * Konstruktor vytvoří danému hráči pistoli
     * @param parent hráč, kterému zbraň patří
     */
    inline explicit HandGun(Player * const parent) :
            Weapon(parent) { this->ammo = 1; }

    /**
     * Implementace abstraktní metody předka (výstřel zbraně)
     */
    void shot(void);

    /**
     * Implementace abstraktní metody předka (doplnění nábojů)
     */
    inline void refill(void) { this->ammo = 1; }

private:

    /**
     * Rychlost střely z pistole
     */
    static double shotSpeed;

};

#endif // HANDGUN_H
