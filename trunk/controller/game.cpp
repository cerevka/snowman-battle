#include "game.h"

Game::Game(QObject * parent) :
        QThread(parent)
{

    allObjects = new QList<MapObject *>();
    allPlayers = new QList<Player *>();
    allShots = new QList<Shot *>();

    gameRun = true;

}

Game::~Game(void)
{

    delete allObjects;
    delete allPlayers;
    delete allShots;

}

void Game::run(void)
{

    while(gameRun){

        moveObjects();
        sendChanges();

    }

}

void Game::quitGame(void)
{
    gameRun = false;
}

void Game::moveObjects(void)
{

    for(int i = 0; i < allPlayers->size(); i++){

        // TODO pohyb hráče ...

        for(int j = 0; j < allObjects->size(); j++){

            if(colideObjects(allObjects->value(j), allPlayers->value(i))){
                allObjects->value(j)->interPlayer(allPlayers->value(i));
            }

        }

    }

    for(int i = 0; i < allShots->size(); i++){

        // TODO pohyb střely ...

        for(int j = 0; j < allObjects->size(); j++){

            if(colideObjects(allObjects->value(j), allShots->value(i))){
                allObjects->value(j)->interShot(allShots->value(i));
            }

        }

    }

}

void Game::sendChanges(void)
{

}

bool Game::colideObjects(MapObject * const first, MapObject * const second)
{
    return colideAlgorythm(first->getX1(), first->getY1(), first->getX2(), first->getY2(), second->getX1(), second->getY1())
            || colideAlgorythm(first->getX1(), first->getY1(), first->getX2(), first->getY2(), second->getX2(), second->getY2());
}

bool Game::colideObjects(MapObject * const object, Shot * const shot)
{
    return colideAlgorythm(object->getX1(), object->getY1(), object->getX2(), object->getY2(), shot->getX(), shot->getY());
}

bool Game::colideAlgorythm(double recX1, double recY1, double recX2, double recY2, double pointX, double pointY)
{

    if(pointX >= recX1 && pointX <= recX2 && pointY >= recY1 && pointY <= recY2){
        return true;
    } else {
        return false;
    }

}
