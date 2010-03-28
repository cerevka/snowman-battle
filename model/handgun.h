#ifndef HANDGUN_H
#define HANDGUN_H

#include "weapon.h"

class HandGun : public Weapon
{

public:

    explicit HandGun(Player * const parent);

    void shot(void);

    void refill(void);

};

#endif // HANDGUN_H
