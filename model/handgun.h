#ifndef HANDGUN_H
#define HANDGUN_H

#include "weapon.h"

/**
 * Tato třída reprezentuje pistoli, kterou každý hráč používá jako základní zbraň
 */
class HandGun : public Weapon
{

public:

    /**
     * Konstruktor vytvoří danému hráči pistoli
     * @param parent hráč, kterému zbraň patří
     */
    explicit HandGun(Player * const parent);

    /**
     * Implementace abstraktní metody předka (výstřel zbraně)
     */
    void shot(void);

    /**
     * Implementace abstraktní metody předka (doplnění nábojů)
     */
    void refill(void);

};

#endif // HANDGUN_H
