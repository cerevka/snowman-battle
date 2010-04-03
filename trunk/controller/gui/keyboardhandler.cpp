#include "keyboardhandler.h"

KeyboardHandler::KeyboardHandler(QObject * const parent, const int myID) :
    QObject(parent)
{

    this->myID = myID;

    // Pokud budeme chtít změnit ovládání, tak je to možná udělat tady

    upKey = Qt::Key_Up;
    downKey = Qt::Key_Down;
    leftKey = Qt::Key_Left;
    rightKey = Qt::Key_Right;

    shotKey = Qt::Key_Space;
    changeKey = Qt::Key_C;
    pauseKey = Qt::Key_Escape;

}

void KeyboardHandler::handleKeyEvent(QKeyEvent * const event)
{

    int key = event->key();
    int type = event->type();

    if(event->isAutoRepeat()){
        return;
    }

    // Klávesa pro pohyb nahoru
    if(key == upKey)
    {
        if(type == QEvent::KeyPress){
            emit upMove(myID);
        } else {
            emit stopMove(myID);
        }
    }
    // Klávesa pro pohyb dolů
    else if (key == downKey)
    {
        if(type == QEvent::KeyPress){
            emit downMove(myID);
        } else {
            emit stopMove(myID);
        }
    }
    // Klávesa pro pohyb doleva
    else if (key == leftKey)
    {
        if(type == QEvent::KeyPress){
            emit leftMove(myID);
        } else {
            emit stopMove(myID);
        }
    }
    // Klávesa pro pohyb doprava
    else if (key == rightKey)
    {
        if(type == QEvent::KeyPress){
            emit rightMove(myID);
        } else {
            emit stopMove(myID);
        }
    }
    // Klávesa pro střelbu
    else if (key == shotKey)
    {
        if(type == QEvent::KeyPress){
            emit shot(myID);
        }
    }
    // Klávesa pro výměnu zbraně
    else if (key == changeKey)
    {
        if(type == QEvent::KeyPress){
            emit changeWeapon(myID);
        }
    }
    // Klávesa pro zastavení hry
    else if (key == pauseKey)
    {
        if(type == QEvent::KeyPress){
            emit pauseGame();
        }
    }

}
