#ifndef SHOOTABLEBLOCK_H
#define SHOOTABLEBLOCK_H

#include "mapobject.h"

class ShootableBlock : public MapObject
{

public:

    ShootableBlock(Game * const parent, const double x1, const double y1, const double x2, const double y2);

    /**
     * Implementace abstraktní metody předka
     * @param player zde nevyužit
     * @return vrací false (překážku nelze přejít)
     */
    bool interactPlayer(Player * const player);

    /**
     * Implementace abstraktní metody předka
     * @param shot zde nevyužit
     * @return vrací true (překážka je přestřelitelná)
     */
    bool interactShot(Shot * const shot);

};

#endif // SHOOTABLEBLOCK_H
