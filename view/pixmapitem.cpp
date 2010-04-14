#include "pixmapitem.h"
#include <QtGui>
#include <iostream>
#include <iomanip>

PixmapItem::PixmapItem(const QString &filename, int w, int h, int x, int y)
{
    if(filename != NULL)
    {
        //Nahrani obrazku
        QPixmap pi(":/images/" + filename);
        this->w = x;
        this->h = y;
        setPixmap(pi.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    }
}

void PixmapItem::changePixmap(const QString &filename, int w, int h)
{
    if(filename != NULL)
    {
        QPixmap pi(":/images/" + filename);
        setPixmap(pi.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}
