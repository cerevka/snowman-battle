#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "weapon.h"

class ShotGun : public Weapon
{
public:
    explicit ShotGun(QObject * parent = 0);
};

#endif // SHOTGUN_H
