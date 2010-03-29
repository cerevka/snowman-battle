#include "scenepanel.h"

ScenePanel::ScenePanel()
{
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 600, 356);
    setScene(scene);
    setCacheMode(CacheBackground);
    setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(QBrush(QColor(255, 255, 200)));
    //setOpeningView();

}

void ScenePanel::setBackground(const QString &background)
{
    setBackgroundBrush(QPixmap(":/images/" + background));
    setSceneRect(0, 0, 800, 490);

}

void ScenePanel::setOpeningView()
{

    PixmapItem *item = new PixmapItem("snowman-stickup.jpg");
    scene->addItem(item);
}

void ScenePanel::setNewGraficObj(PixmapItem &item, int x, int y, int direction)
{
    scene->addItem(&item);
    item.setPos(x, y);
    setDirection(item, direction);
}

void ScenePanel::removeGraficObj(PixmapItem &item)
{
    scene->removeItem(&item);
}

void ScenePanel::setDirection(PixmapItem &item, int direction)
{
    switch (direction)
    {
    case 0:
        {
            break;
        }
    case 1:
        {
            item.rotate(-90);
            break;
        }
    case 2:
        {
            item.rotate(180);
            break;
        }
    case 3:
        {
            item.rotate(90);
            break;
        }
    }
}

void ScenePanel::setPosition(PixmapItem &item, int x, int y)
{
    item.setPos(x, y);
}

