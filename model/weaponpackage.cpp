#include "weaponpackage.h"
#include "player.h"
#include "weapon.h"
#include "../controller/game/game.h"
#include "cstdlib"
#include "ctime"
using namespace std;

WeaponPackage::WeaponPackage(Game * const parent) :
        MapObject(parent)
{

    if(time(NULL) * rand() > 0.7){
        type = SHOTGUN;
    } else {
        type = MACHINEGUN;
    }

}

bool WeaponPackage::interactPlayer(Player * const player)
{

    switch(type){

    case MACHINEGUN:
        {
            player->getInventory()[1]->refill();

            break;
        }

    case SHOTGUN:
        {
            player->getInventory()[2]->refill();

            break;
        }

    default:
        {
            break;
        }

    }

    parentGame->removeWeaponPackage(this);

    return true;
}

bool WeaponPackage::interactShot(Shot * const shot)
{
    return true;
}

WeaponType WeaponPackage::getType(void) const
{
    return type;
}
