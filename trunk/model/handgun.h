#ifndef HANDGUN_H
#define HANDGUN_H

#include "weapon.h"

/**
 * Tato třída reprezentuje pistoly, kterou každý hráč používá jako základní zbraň
 */
class HandGun : public Weapon
{

public:

    explicit HandGun(Player * const parent);

    void shot(void);

    void refill(void);

};

#endif // HANDGUN_H
