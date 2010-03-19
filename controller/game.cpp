#include "game.h"

Game::Game(QObject * parent) :
        QThread(parent)
{

    gameRun = true;

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

}

void Game::sendChanges(void)
{

}
