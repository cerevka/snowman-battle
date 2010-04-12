#include "weaponpackage.h"
#include "player.h"
#include "weapon.h"
#include "../controller/game/game.h"

QBitArray WeaponPackage::idArray = QBitArray(256);
double WeaponPackage::weaponPackageSize = 30.0;

WeaponPackage::WeaponPackage(Game * const parent) :
        MapObject(parent)
{

    // Vygeneruji náhodné souřadnice
    parent->generateValidCoordinates(weaponPackageSize, this);

    // Vygeneruji náhodný typ zbraně
    if((qrand()%10) > 7){
        type = SHOTGUN;
    } else {
        type = MACHINEGUN;
    }

    weaponPackageID = 0;

    // Vyhledám nejbližší volné ID
    for(int i = 0; i < idArray.size(); i++){
        if(idArray[i] == false){
            weaponPackageID = i;
            idArray[i] = true;
            break;
        }

        if(i == idArray.size()){
            throw QString(tr("Too many weapon packages (over 256)"));
        }
    }

}

WeaponPackage::~WeaponPackage(void)
{

    idArray[weaponPackageID] = false;

}

bool WeaponPackage::interactPlayer(Player * const player)
{

    // Podle typu zbraně doplním danému hráč i náboje
    switch(type){

    case MACHINEGUN:
        {
            player->getInventory()[1]->refill();
            player->setActualWeapon(1);

            break;
        }

    case SHOTGUN:
        {
            player->getInventory()[2]->refill();
            player->setActualWeapon(2);

            break;
        }

    default:
        {
            break;
        }

    }

    // Odstraním zbraň ze seznamů
    parentGame->removeWeaponPackage(this);

//    delete this;

    return true;
}

bool WeaponPackage::interactShot(Shot * const)
{
    return true;
}

int WeaponPackage::getWeaponPackageID(void) const
{
    return weaponPackageID;
}

WeaponType WeaponPackage::getType(void) const
{
    return type;
}
