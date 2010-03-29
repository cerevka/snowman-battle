#include "handgun.h"
#include "../controller/game.h"
#include "player.h"
#include "shot.h"
#include "cmath"
using namespace std;

HandGun::HandGun(Player * const parent) :
        Weapon(parent)
{
    this->refill();
}

void HandGun::shot(void)
{

    double x;
    double y;
    double angle;

    double speed = 1.0;

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

    Shot * newShot = new Shot(owner, x, y, angle, speed);

    owner->getParentGame()->addShot(newShot);

}

void HandGun::refill(void)
{

    ammo = 1;

}
