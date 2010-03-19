#ifndef SHOOTABLEBLOCK_H
#define SHOOTABLEBLOCK_H

#include "immovable.h"

class ShootableBlock : public Immovable
{
public:
    explicit ShootableBlock(QObject * parent = 0);
};

#endif // SHOOTABLEBLOCK_H
