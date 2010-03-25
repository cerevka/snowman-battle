#ifndef PLAYER_H
#define PLAYER_H

#include "mapobject.h"

// Výčtový typ pro směr hráče
enum Directions
{
    NORTH, WEST, SOUTH, EAST
};

class Player : public MapObject
{

public:

    explicit Player(QObject * parent = 0);

    Directions getDirection(void) const;
    void setDirection(const Directions direction);
    bool isMoving(void) const;
    void setMoving(const bool moving);

private:

    Directions direction;
    bool moving;

};

#endif // PLAYER_H
