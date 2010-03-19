#ifndef GAME_H
#define GAME_H

#include "../model/mapobject.h"
#include "../model/player.h"
#include "../model/shot.h"
#include <QThread>

class Game : public QThread
{
public:

    explicit Game(QObject * parent = 0);

    void quitGame(void);

protected:

    virtual void run(void);

private:

    bool gameRun;

    QList<MapObject> allObject;
    QList<Player> allPlayers;
    QList<Shot> allShots;

    void moveObjects(void);
    void sendChanges(void);

};

#endif // GAME_H
