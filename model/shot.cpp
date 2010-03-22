#include "shot.h"

Shot::Shot(QObject * parent) :
    QObject(parent)
{
}

double Shot::getX(void) const
{
    return x;
}

double Shot::getY(void) const
{
    return y;
}
