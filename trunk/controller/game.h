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

    virtual ~Game(void);

    void quitGame(void);

protected:

    virtual void run(void);

private:

    bool gameRun;

    QList<MapObject *> * allObjects;
    QList<Player *> * allPlayers;
    QList<Shot *> * allShots;

    void moveObjects(void);
    void sendChanges(void);

    // pomocné metody, které se používají k detekci kolizí
    bool colideObjects(MapObject * const first, MapObject * const second);
    bool colideObjects(MapObject * const object, Shot * const shot);
    bool colideAlgorythm(double recX1, double recY1, double recX2, double recY2, double pointX, double pointY);

};

#endif // GAME_H
