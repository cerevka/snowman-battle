#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>


class KeyboardHandler : public QObject
{

Q_OBJECT

public:

    explicit KeyboardHandler(QObject * parent = 0);

    void handleKeyEvent(QKeyEvent * const event);

signals:

    void upMove(void);
    void downMove(void);
    void leftMove(void);
    void rightMove(void);

    void stopMove(void);

    void shot(void);

    void changeWeapon(void);

    void pauseGame(void);

private:

    int upKey;
    int downKey;
    int leftKey;
    int rightKey;

    int shotKey;
    int changeKey;
    int pauseKey;

};

#endif // KEYBOARDHANDLER_H
