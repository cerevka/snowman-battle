#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H

#include <QtGui/QGraphicsPixmapItem>

/**
  * Trida, ktera reprezentuje graficke objekty ve hre
  */
class PixmapItem : public QGraphicsPixmapItem
{

public:

    /**
      * Vytvori graficky objekt
      * @param filename jemno obrazku, ktery chceme nahrat
      * @parem w sirka obrazku
      * @param h vyska obrazku
      * @param x x-ovy rozmer obrazku kvuli rotaci
      * @param y y-ovy rozmer obrazku kvuli rotaci
      */
    PixmapItem(const QString &filename, int w, int h, int x, int y);

    /**
      * Vyska obrazku
      */
    int h;

    /**
      * Sirska obrazku
      */
    int w;
};

#endif // PIXMAPITEM_H
