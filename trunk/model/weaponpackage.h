#ifndef WEAPONPACKAGE_H
#define WEAPONPACKAGE_H

#include "immovable.h"

class WeaponPackage : public Immovable
{
public:
    explicit WeaponPackage(QObject * parent = 0);
};

#endif // WEAPONPACKAGE_H
