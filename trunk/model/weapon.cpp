#include "weapon.h"
#include "player.h"
#include "cmath"

Weapon::Weapon(Player * const parent) :
    QObject((QObject *)parent)
{
    ammo = 1;
    owner = parent;
}

int Weapon::getAmmo(void) const
{
    return ammo;
}

void Weapon::findPointOfCreatingShots(double & x, double & y, double & angle)
{
    switch(owner->getDirection()){

    case NORTH:
        {
            x = (owner->getX1() + owner->getX2()) / 2.0;
            y = owner->getY1() - 1.0;
            angle = M_PI / 2;

            break;
        }

    case WEST:
        {
            x = owner->getX1() - 1.0;
            y = (owner->getY1() + owner->getY2()) / 2.0;
            angle = M_PI;

            break;
        }

    case SOUTH:
        {
            x = (owner->getX1() + owner->getX2()) / 2.0;
            y = owner->getY2() + 1.0;
            angle = 3.0 * M_PI / 2.0;

            break;
        }

    case EAST:
        {
            x = owner->getX2() + 1.0;
            y = (owner->getY1() + owner->getY2()) / 2.0;
            angle = 0.0;

            break;
        }

    }
}

