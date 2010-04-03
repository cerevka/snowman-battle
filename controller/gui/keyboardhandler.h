#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>

/**
 * Tato třída se napojí na grafický prvek a na něm odchytává herní klávesy a podle nich posílá signály
 */
class KeyboardHandler : public QObject
{

Q_OBJECT

public:

    explicit KeyboardHandler(QObject * const parent, const int myID);

    void handleKeyEvent(QKeyEvent * const event);

signals:

    void upMove(const int);
    void downMove(const int);
    void leftMove(const int);
    void rightMove(const int);

    void stopMove(const int);

    void shot(const int);

    void changeWeapon(const int);

    void pauseGame(void);

private:

    int myID;

    int upKey;
    int downKey;
    int leftKey;
    int rightKey;

    int shotKey;
    int changeKey;
    int pauseKey;

};

#endif // KEYBOARDHANDLER_H
