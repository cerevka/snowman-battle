#ifndef SHOT_H
#define SHOT_H

#include <QObject>

class Shot : public QObject
{

    Q_OBJECT

public:
    explicit Shot(QObject * parent = 0);

};

#endif // SHOT_H
