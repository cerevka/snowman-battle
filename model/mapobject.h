#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <QObject>

class Player;
class Shot;

class MapObject : public QObject
{

    Q_OBJECT

public:

    explicit MapObject(QObject * parent = 0);

    // jak se objekt zachová, když na něj vběhne hráč
    virtual void interPlayer(Player * const player) = 0;

    // jak se objekt zachová, když do něj vletí střela
    virtual void interShot(Shot * const shot) = 0;

    double getX1(void) const;
    double getY1(void) const;

    double getX2(void) const;
    double getY2(void) const;

protected:

    // levý horní roh
    double x1;
    double y1;

    // pravý dolní roh
    double x2;
    double y2;

};

#endif // MAPOBJECT_H
