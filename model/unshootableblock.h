#ifndef UNSHOOTABLEBLOCK_H
#define UNSHOOTABLEBLOCK_H

#include "immovable.h"

class UnshootableBlock : public Immovable
{
public:
    explicit UnshootableBlock(QObject * parent = 0);
};

#endif // UNSHOOTABLEBLOCK_H
