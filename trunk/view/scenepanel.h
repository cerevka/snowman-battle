#ifndef SCENEPANEL_H
#define SCENEPANEL_H

#include <QWidget>
#include <QtGui>
#include <QtGui/QGraphicsView>
#include <QVector>
#include "pixmapitem.h"

#include "../controller/gui/keyboardhandler.h"
#include "../controller/game/gamefacade.h"

class QLabel;

/**
  * Trida reprezentujici hraci plochu
  */
class ScenePanel : public QGraphicsView
{
Q_OBJECT
public:

    /**
      * Vytvori hraci plochu
      */
    explicit ScenePanel();

    /**
      * Nastavi obrazek na pozadi
      * @param background nazev obrazku
      */
    void setBackground(const QString &background);

    /**
      * Nastavi uvodni obrazek
      */
    void setOpeningView();

signals:
    void changeAmmo(int id, int ammo);

public slots:
    /**
      * Prida noveho hrace
      * @param id id hrace
      * @param x x-ova souradnice objektu
      * @param y y-ova souradnice objektu
      * @param direction orientace objektu
      */
    void addNewPlayer(int id, int x, int y, int direction);

    /**
      * Prida novou zbran
      * @param id id zbrane
      * @param x x-ova souradnice objektu
      * @param y y-ova souradnice objektu
      * @param type typ zbrane
      */
    void addNewGun(int id, int x, int y, int type);

    /**
      * Prida novou strelu
      * @param id id strely
      * @param x x-ova souradnice objektu
      * @param y y-ova souradnice objektu
      */
    void addNewShot(int id, int x, int y);

    /**
      * Zmeni hracovu zbran
      * @param id id hrace
      * @param type typ zbrane
      */
    void changeGun(int id, int type, int restAmmo);

    /**
      * Zmeni hracovu pozici
      * @param id id hrace
      * @param x x-ova souradnice objektu
      * @param y y-ova souradnice objektu
      */
    void changePlayerPosition(int id, int x, int y);

    /**
      * Zmeni pozici strely
      * @param id id strely
      * @param x x-ova souradnice objektu
      * @param y y-ova souradnice objektu
      */
    void changeShotPosition(int id, int x, int y);

    /**
      * Zmeni orientaci hrace
      * @param id id hrace
      * @param direction pozadovana orientace
      */
    void changePlayerDirection(int id, int direction);

    /**
      * Odstrani strelu
      * @param id id strely
      */
    void removeShot(int id);

    /**
      * Odstrani zbran
      * @param id zbrene
      */
    void removeGun(int id);

    /**
      * Shryje hrace
      * @param id id hrece
      */
    void hidePlayer(int id);

    /**
      * Zjeveni hrace na pozici
      * @param id id hrace
      * @param x x-ova souradnice objektu
      * @param y y-ova souradnice objektu
      * @param direction pozadovana orientace hrace
      */
    void appearePlayer(int id, int x, int y, int direction);

    ///// Testování Ota

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

    ///// Konec testování Ota

private:

    /**
      * Prida novy graficky objekt na hraci plochu
      * @param id id grafickeho objektu
      * @param x x-ova souradnice objektu
      * @param y y-ova souradnice objektu
      * @param direction orientace objektu
      */
    void setNewGraficObj(int id, int x, int y, int direction);

    /**
      * Odstrani objekt z hraci plochy
      * @param id id grafickeho objektu
      */
    void removeGraficObj(int id);

    /**
      * Presune objekt na pozici [x,y]
      * @param id id grafickeho objektu
      * @param x x-ova souradnice objektu
      * @param y y-ova souradnice objektu
      */
    void setPosition(int id, int x, int y);

    /**
      * Nastavi orientaci objektu
      * @param id id grafickeho objektu
      * @param direction pozadovana orientace
      */
    void setDirection(int id, int direction);

    /**
      * Skryje objekt
      * @param id id objektu
      */
    void hideObject(int id);

    /**
      * Zobrazi objekt na plose
      * @param id id objektu
      * @param x x-ova souradnice objektu
      * @param y y-ova souradnice objektu
      * @param direction orientace objektu
      */

    void appearObject(int id, int x, int y, int direction);

    QGraphicsScene *scene;

    /// Testování Ota
    KeyboardHandler * handler;

    /**
      * Vektor referenci na objekt PixmapItem
      * pozice 0 - 5 reference na hrace
      * pozice 6 - 23 reference na zbrane hracu
      * pozice 24 - 279 reference na volne zbrane
      * pozice 280 - 535 reference na strely
      */
    QVector<PixmapItem *> items;

    /**
      * Vyska hrace
      */
    const static int playerH = 55;

    /**
      * Sirska hrace
      */
    const static int playerW = 97;

    /**
      * Vyska pistole
      */
    const static int gunH = 40;

    /**
      * Sirska pistole
      */
    const static int gunW = 20;

    /**
      * Vyska samopalu
      */
    const static int machinegunH = 70;

    /**
      * Sirska samopalu
      */
    const static int machinegunW = 21;

    /**
      * Rozmery strely
      */
    const static int shotS = 10;

    /**
      * Pocet zbrani, ktere muze hrac vlastnit
      */
    const static int guns = 3;

    /**
      * Pripocitava se k id zbrane pro mapovani do pole
      */
    const static int plusIdGuns = 24;

    /**
      * Pripocitava se k id strely pro mapovani do pole
      */
    const static int plusIdShots = 280;

    /**
      * Jednotlive barvy hracu
      */
    QStringList colors;

};

#endif // SCENEPANEL_H
