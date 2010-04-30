
#include "mapobject.h"

MapObject::MapObject(Game * const parent, const double x1, const double y1, const double x2, const double y2) :
    QObject()
{

    this->moveToThread((QThread *)parent);
    this->setParent((QObject *)parent);

    this->parentGame = parent;

    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;

}

