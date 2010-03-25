#include "weaponpackage.h"

WeaponPackage::WeaponPackage(QObject * parent) :
        Immovable(parent)
{
}

WeaponType WeaponPackage::getType(void) const
{
    return type;
}
