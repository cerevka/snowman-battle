#ifndef MACHINEGUN_H
#define MACHINEGUN_H

#include "weapon.h"

class MachineGun : public Weapon
{
public:
    explicit MachineGun(QObject * parent = 0);
};

#endif // MACHINEGUN_H
