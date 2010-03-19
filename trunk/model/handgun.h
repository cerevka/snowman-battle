#ifndef HANDGUN_H
#define HANDGUN_H

#include "weapon.h"

class HandGun : public Weapon
{
public:
    explicit HandGun(QObject * parent = 0);
};

#endif // HANDGUN_H
