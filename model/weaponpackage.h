#ifndef WEAPONPACKAGE_H
#define WEAPONPACKAGE_H

#include "immovable.h"

enum WeaponType
{
    HANDGUN, SHOTGUN, MACHINEGUN
};

class WeaponPackage : public Immovable
{

public:

    explicit WeaponPackage(QObject * parent = 0);

    WeaponType getType(void) const;

protected:

    WeaponType type;

};

#endif // WEAPONPACKAGE_H
