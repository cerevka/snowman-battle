#include "keyboardhandler.h"

KeyboardHandler::KeyboardHandler(QObject * parent) :
    QObject(parent)
{

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

    // Klávesa pro pohyb nahoru
    if(key == upKey)
    {
        if(type == QEvent::KeyPress){
            emit upMove();
        } else {
            emit stopMove();
        }
    }
    // Klávesa pro pohyb dolů
    else if (key == downKey)
    {
        if(type == QEvent::KeyPress){
            emit downMove();
        } else {
            emit stopMove();
        }
    }
    // Klávesa pro pohyb doleva
    else if (key == leftKey)
    {
        if(type == QEvent::KeyPress){
            emit leftMove();
        } else {
            emit stopMove();
        }
    }
    // Klávesa pro pohyb doprava
    else if (key == rightKey)
    {
        if(type == QEvent::KeyPress){
            emit rightMove();
        } else {
            emit stopMove();
        }
    }
    // Klávesa pro střelbu
    else if (key == shotKey)
    {
        if(type == QEvent::KeyPress){
            emit shot();
        }
    }
    // Klávesa pro výměnu zbraně
    else if (key == changeKey)
    {
        if(type == QEvent::KeyPress){
            emit changeWeapon();
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
