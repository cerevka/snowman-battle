#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "weapon.h"

class ShotGun : public Weapon
{

public:

    explicit ShotGun(Player * const parent);

    void shot(void);

    void refill(void);

};

#endif // SHOTGUN_H