#ifndef SCENEPANEL_H
#define SCENEPANEL_H

#include <QWidget>
#include <QtGui>
#include <QtGui/QGraphicsView>
#include "pixmapitem.h"

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

    /**
      * Prida novy graficky objekt na hraci plochu
      * @param item graficky objekt
      * @param x x-ova souradnice objektu
      * @param y y-ova souradnice objektu
      * @param direction orientace objektu
      */
    void setNewGraficObj(PixmapItem &item, int x, int y, int direction);

    /**
      * Odstrani objekt z hraci plochy
      * @param item graficky objekt
      */
    void removeGraficObj(PixmapItem &item);

    /**
      * Presune objekt na pozici [x,y]
      * @param item graficky objekt
      * @param x x-ova souradnice objektu
      * @param y y-ova souradnice objektu
      */
    void setPosition(PixmapItem &item, int x, int y);

    /**
      * Nastavi orientaci objektu
      * @param item graficky objekt
      * @param direction pozadovana orientace
      */
    void setDirection(PixmapItem &item, int direction);

private:
    QGraphicsScene *scene;

};

#endif // SCENEPANEL_H
