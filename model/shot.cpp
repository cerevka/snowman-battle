#include "shot.h"
#include "cmath"
using namespace std;

QBitArray Shot::idArray = QBitArray(256);

Shot::Shot(const double x, const double y, const double angle, const double speed, Player * const parent) :
    QObject((QObject *)parent)
{

    this->x = x;
    this->y = y;
    this->angle = angle;
    this->speed = speed;

    owner = parent;

    shotID = 0;

    for(int i = 0; i < idArray.size(); i++){
        if(idArray[i] == false){
            shotID = i;
            idArray[i] = true;
            break;
        }

        if(i == idArray.size()){
            throw QString(tr("Too many shots (over 256)"));
        }
    }

}

Shot::~Shot(void)
{

    idArray[shotID] = false;

}

void Shot::move(void)
{
    x = x + cos(angle) * speed;
    y = y + (-1 * sin(angle)) * speed;
}

Player * Shot::getOwner(void) const
{
    return owner;
}

int Shot::getShotID(void) const
{
    return shotID;
}

double Shot::getX(void) const
{
    return x;
}

double Shot::getY(void) const
{
    return y;
}
