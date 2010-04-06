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

    /**
     * Konstruktor vytvoří "odchytavač" kláves
     * @param parent grafický prvek, na který je tento objekt napojen
     * @param myID id lokálního hráče
     */
    KeyboardHandler(QObject * const parent, const int myID);

    /**
     * Tato metoda rozpozná daný key event a podle toho vyšle odpovídající signál
     * @param event key event, který se má zpracovat
     */
    void handleKeyEvent(QKeyEvent * const event);

signals:

    /**
     * Tyto signály jsou vyslány, když je stisknuta odpovídající směrová klávesa
     */
    void upMove(const int);
    void downMove(const int);
    void leftMove(const int);
    void rightMove(const int);

    /**
     * Tento signál je vyslán, když je puštěna pohybová klávesa
     */
    void stopMove(const int);

    /**
     * Toto je signál stisknutí talčítka pro střelbu
     */
    void shot(const int);

    /**
     * Toto je signál stisknutí talčítka pro změnu zbraně
     */
    void changeWeapon(const int);

    /**
     * Toto je signál stisknutí talčítka pro pozastavení hry
     */
    void pauseGame(void);

private:

    /**
     * Id lokálního hráce
     */
    int myID;

    /**
     * Zde jsou uloženy klávesy, které k daným akcím patří
     */
    int upKey;
    int downKey;
    int leftKey;
    int rightKey;

    int shotKey;
    int changeKey;
    int pauseKey;

};

#endif // KEYBOARDHANDLER_H
