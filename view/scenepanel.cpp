#include "scenepanel.h"

ScenePanel::ScenePanel()
{
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 875, 567);
    setScene(scene);
    setCacheMode(CacheBackground);
    setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(QBrush(QColor(255, 255, 200)));

    items.resize(536);

    colors << "black" << "red" << "blue" << "green" << "brown" << "yellow";
    //setOpeningView();

    ///// Testování Ota

    GameFacade * const facade = new GameFacade();
    facade->newGame(6);
    handler = new KeyboardHandler(NULL, 0);
    connect(handler, SIGNAL(upMove(int)), facade, SLOT(startMoveNorth(int)));
    connect(handler, SIGNAL(downMove(int)), facade, SLOT(startMoveSouth(int)));
    connect(handler, SIGNAL(leftMove(int)), facade, SLOT(startMoveWest(int)));
    connect(handler, SIGNAL(rightMove(int)), facade, SLOT(startMoveEast(int)));
    connect(handler, SIGNAL(stopMove(int)), facade, SLOT(stopMove(int)));
    connect(handler, SIGNAL(shot(int)), facade, SLOT(shot(int)));
    connect(handler, SIGNAL(changeWeapon(int)), facade, SLOT(changeWeapon(int)));
    connect(handler, SIGNAL(pauseGame()), facade, SLOT(pauseGame()));

    ///// Konec testování Ota

}

void ScenePanel::setBackground(const QString &background)
{
    setBackgroundBrush(QPixmap(":/images/" + background));
    setSceneRect(0, 0, 875, 567);

}

void ScenePanel::setOpeningView()
{

    PixmapItem *item = new PixmapItem("snowman-stickup.jpg", 1000, 800, 1000, 800);
    scene->addItem(item);
}

void ScenePanel::setNewGraficObj(int id, int x, int y, int direction)
{

    if(items.at(id) != NULL)
    {
        scene->addItem(items.at(id));
        items.at(id)->setPos(x, y);
        setDirection(id, direction);
    }
}

void ScenePanel::removeGraficObj(int id)
{
    if(items.at(id) != NULL)
    {
        scene->removeItem(items.at(id));
        delete items.at(id);
        items[id] = NULL;
    }
}

void ScenePanel::hideObject(int id)
{
    if(items.at(id) != NULL && items.at(id)->isVisible())
        items.at(id)->hide();
}

void ScenePanel::appearObject(int id, int x, int y, int direction)
{
    if(items.at(id) != NULL && !items.at(id)->isVisible())
    {
        items.at(id)->setPos(x, y);
        setDirection(id, direction);
        items.at(id)->show();

    }
}

void ScenePanel::setDirection(int id, int direction)
{
    if(items.at(id) != NULL)
    {
        // Zjisteni souradnic podle kterych se bude provadet rotace
        int x = items.at(id)->w / 2;
        int y = items.at(id)->h / 2;


        switch (direction)
        {
            // Orientace nahoru
        case 0:
            {
                items.at(id)->setTransform(QTransform().translate(x, y).rotate(0).translate(-x, -y));
                break;
            }
            // Orientace doprava
        case 1:
            {
                items.at(id)->setTransform(QTransform().translate(x, y).rotate(90).translate(-x, -y));
                break;
            }
            // Orientace dolu
        case 2:
            {
                items.at(id)->setTransform(QTransform().translate(x, y).rotate(180).translate(-x, -y));
                break;
            }
            // Orientace doleva
        case 3:
            {
                items.at(id)->setTransform(QTransform().translate(x, y).rotate(-90).translate(-x, -y));
                break;
            }
        }
    }
}

void ScenePanel::setPosition(int id, int x, int y)
{
    if(items.at(id) != NULL)
        items.at(id)->setPos(x, y);
}

void ScenePanel::addNewPlayer(int id, int x, int y, int direction)
{
    if(items.at(id) != NULL)
        removeGraficObj(id);

    items[id] = new PixmapItem("snowman_" + colors.at(id) + ".png", playerW, playerH, playerW, playerH);
    items.at(id)->dir = direction;
    setNewGraficObj(id, x, y, direction);

    // Nastavi inventar zbrani
    addNewGun(6 + id * guns - plusIdGuns, x + playerW * 0.67, y, direction, 0);
    items.at(id)->actGun = 6 + id * guns;
    addNewGun(6 + id * guns + 1 - plusIdGuns, x + playerW * 0.67, y, direction, 1);
    hideObject(6 + id * guns + 1);
    addNewGun(6 + id * guns + 2 - plusIdGuns, x + playerW * 0.67, y, direction, 2);
    hideObject(6 + id * guns + 2);
}

void ScenePanel::addNewGun(int id, int x, int y, int direction, int type)
{
    id += plusIdGuns;

    if(items.at(id) != NULL)
        removeGraficObj(id);

    switch(type)
    {
        // Pistol
    case 0:
        items[id] = new PixmapItem("gun.png", gunW, gunH, gunW - 50, gunH + 10);
        setNewGraficObj(id, x, y, direction);
        break;

        // Samopal
    case 1:
        items[id] = new PixmapItem("machine_gun.png", machinegunW, machinegunH, machinegunW - 50, machinegunH - 10);
        setNewGraficObj(id, x, y, direction);
        break;

        // Brokovnice
    case 2:
        items[id] = new PixmapItem("shot_gun.png", machinegunW, machinegunH, machinegunW, machinegunH);
        setNewGraficObj(id, x, y, direction);
        break;
    }

}

void ScenePanel::addNewShot(int id, int x, int y)
{
    //Mapovani ID do pole
    id += plusIdShots;

    // Nastaveni pozice na stred naboje
    x += shotS / 2;
    y += shotS / 2;

    if(items.at(id) != NULL)
        removeGraficObj(id);

    items[id] = new PixmapItem("shot.png", shotS, shotS, shotS, shotS);
    setNewGraficObj(id, x, y, 0);

}

void ScenePanel::changeGun(int id, int type)
{
    int p = id * 3 + 6;
    hideObject(items.at(id)->actGun);

    items.at(id)->actGun = p + type;
    appearObject(p + type, items.at(id)->x() + playerW * 0.67, items.at(id)->y(), items.at(id)->dir);
}

void ScenePanel::changePlayerPosition(int id, int x, int y)
{
    int pos = items.at(id)->dir;
    int idGun = items.at(id)->actGun;
    int px = items.at(id)->x() - x;
    int py = items.at(id)->y() - y;

    if(px < 0 && pos != 1)
        changePlayerDirection(id, 1);
    if(px > 0 && pos != 3)
        changePlayerDirection(id, 3);
    if(py > 0 && pos != 0)
        changePlayerDirection(id, 0);
    if(py < 0 && pos != 2)
        changePlayerDirection(id, 2);

    setPosition(id, x, y);
    setPosition(idGun, x + playerW * 0.67, y);

}

void ScenePanel::changePlayerDirection(int id, int direction)
{
    setDirection(id, direction);
    setDirection(items.at(id)->actGun, direction);
}

void ScenePanel::changeShotPosition(int id, int x, int y)
{
    setPosition(id + plusIdShots, x, y);
}

void ScenePanel::removeShot(int id)
{
    removeGraficObj(id + plusIdShots);
}

void ScenePanel::removeGun(int id)
{
    removeGraficObj(id + plusIdGuns);
}

void ScenePanel::hidePlayer(int id)
{
    hideObject(id);
    hideObject(items.at(id)->actGun);
}

void ScenePanel::appearePlayer(int id, int x, int y, int direction)
{
    appearObject(id, x, y, direction);
    appearObject(items.at(id)->actGun, x + playerW * 0.67, y, direction);
}

///// Testování Ota

void ScenePanel::keyPressEvent(QKeyEvent * event)
{

    QWidget::keyPressEvent(event);

    handler->handleKeyEvent(event);

}

void ScenePanel::keyReleaseEvent(QKeyEvent * event)
{

    QWidget::keyReleaseEvent(event);

    handler->handleKeyEvent(event);

}

///// Konec testování Ota

