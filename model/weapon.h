#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>

class Weapon : public QObject
{
Q_OBJECT
public:
    explicit Weapon(QObject *parent = 0);

signals:

public slots:

};

#endif // WEAPON_H
