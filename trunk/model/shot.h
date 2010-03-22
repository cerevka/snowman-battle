#ifndef SHOT_H
#define SHOT_H

#include <QObject>

class Shot : public QObject
{

    Q_OBJECT

public:

    explicit Shot(QObject * parent = 0);

    double getX(void) const;
    double getY(void) const;

private:

    double x;
    double y;
    double angle;
    double speed;

};

#endif // SHOT_H
