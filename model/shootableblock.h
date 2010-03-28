#ifndef SHOOTABLEBLOCK_H
#define SHOOTABLEBLOCK_H

#include "immovable.h"

class ShootableBlock : public Immovable
{

public:

    explicit ShootableBlock(Game * const parent = 0);

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
