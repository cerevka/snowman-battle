#include "mapobject.h"

MapObject::MapObject(Game * const parent, const double x1, const double y1, const double x2, const double y2) :
    QObject()
{

    this->moveToThread(QApplication::instance()->thread());
    this->setParent((QObject *)parent);

    this->parentGame = parent;

    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;

}


double MapObject::getX1(void) const
{
    return x1;
}

double MapObject::getY1(void) const
{
    return y1;
}


double MapObject::getX2(void) const
{
    return x2;
}

double MapObject::getY2(void) const
{
    return y2;
}
