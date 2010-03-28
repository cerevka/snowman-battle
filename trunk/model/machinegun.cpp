#include "machinegun.h"

MachineGun::MachineGun(Player * const parent) :
        Weapon(parent)
{

    this->refill();

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
