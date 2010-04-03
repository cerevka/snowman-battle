#include "handgun.h"
#include "../controller/game/game.h"
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

    findPointOfCreatingShots(x, y, angle);

    Shot * newShot = new Shot(x, y, angle, speed);

    owner->getParentGame()->addShot(newShot);

}

void HandGun::refill(void)
{

    ammo = 1;

}
