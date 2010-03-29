#include "pixmapitem.h"

PixmapItem::PixmapItem(const QString &filename)
{
    if(filename != NULL)
    {
        //Nahrani obrazku
        setPixmap(":/images/" + filename);
    }
}
