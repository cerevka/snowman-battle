#ifndef UNSHOOTABLEBLOCK_H
#define UNSHOOTABLEBLOCK_H

#include "mapobject.h"

/**
 * Tato třída reprezentuje překážky, přes které nelze střelit (např. skála)
 * @author Ota Sandr
 */
class UnshootableBlock : public MapObject
{

    Q_OBJECT

public:

    /**
     * Vytvoří přestřelitelnou překážku na zadaných souřadnicích
     * @param parent hra v rámci níž je tato překážka vytvořena
     * @param x1 x-ová souřadnice levého horního rohu překážky
     * @param y1 y-ová souřadnice levého horního rohu překážky
     * @param x2 x-ová souřadnice pravého dolního rohu překážky
     * @param y2 y-ová souřadnice pravého dolního rohu překážky
     */
    inline UnshootableBlock(Game * const parent, const double x1, const double y1, const double x2, const double y2) :
            MapObject(parent, x1, y1, x2, y2) {}

    /**
     * Implementace abstraktní metody předka
     * @param player zde nevyužit
     * @return vrací false (překážku nelze přejít)
     */
    inline bool interactPlayer(Player * const) { return false; }

    /**
     * Implementace abstraktní metody předka
     * @param shot zde nevyužit
     * @return vrací false (překážka není přestřelitelná)
     */
    inline bool interactShot(Shot * const) { return false; }

};

#endif // UNSHOOTABLEBLOCK_H
