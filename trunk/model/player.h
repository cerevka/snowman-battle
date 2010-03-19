#ifndef PLAYER_H
#define PLAYER_H

#include "mapobject.h"

class Player : public MapObject
{
public:
    explicit Player(QObject * parent = 0);
};

#endif // PLAYER_H
