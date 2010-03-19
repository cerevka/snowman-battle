#include "mapobject.h"

MapObject::MapObject(QObject * parent) :
    QObject(parent)
{
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
