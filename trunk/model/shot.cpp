#include "shot.h"
#include "cmath"
using namespace std;

Shot::Shot(QObject * const parent, const double x, const double y, const double angle, const double speed) :
    QObject(parent)
{

    this->x = x;
    this->y = y;
    this->angle = angle;
    this->speed = speed;

}

void Shot::move(void)
{
    x = x + cos(angle) / speed;
    y = y + sin(angle) / speed;
}

double Shot::getX(void) const
{
    return x;
}

double Shot::getY(void) const
{
    return y;
}
