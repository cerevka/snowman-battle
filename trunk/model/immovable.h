#ifndef IMMOVABLE_H
#define IMMOVABLE_H

#include "mapobject.h"

class Immovable : public MapObject
{
public:
    explicit Immovable(QObject * parent = 0);
};

#endif // IMMOVABLE_H
