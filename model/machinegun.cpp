#include "machinegun.h"

MachineGun::MachineGun(Player * const parent) :
        Weapon(parent)
{

    ammo = 0;

}

void MachineGun::shot(void)
{

    // TODO - doplnit výstřel zbraně

    ammo--;

}

void MachineGun::refill(void)
{

    ammo = 5;

}
