#ifndef MACHINEGUN_H
#define MACHINEGUN_H

#include "weapon.h"

class MachineGun : public Weapon
{

public:

    explicit MachineGun(Player * const parent);

    void shot(void);

    void refill(void);

};

#endif // MACHINEGUN_H
