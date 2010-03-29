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
      */
    PixmapItem(const QString &filename);
};

#endif // PIXMAPITEM_H
