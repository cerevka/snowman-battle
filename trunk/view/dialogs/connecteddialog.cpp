#include "connecteddialog.h"
#include "globals.h"

static const QSize resultSize(80, 65);

ConnectedDialog::ConnectedDialog(QWidget *parent)
    : QDialog(parent)
{
    colors << "black" << "red" << "blue" << "green" << "brown" << "yellow";


    QLabel *lab = new QLabel(tr("ceka se na hrace"));
    QPushButton *but = new QPushButton(tr("create"));

    layout = new QGridLayout;
    layout->addWidget(lab, 0, 0);
    layout->addWidget(but, 1, 0);
    setLayout(layout);

    connect(but, SIGNAL(clicked()), Globals::gameFacade, SLOT(newGame(int)));
}

void ConnectedDialog::addPlayer(int id)
{
    QString *name = Globals::mainWindow->getName(id);
    switch(id)
    {
    case 0:
        name1 = new QLabel("<font color=" + colors.at(id) +">" + *name + "</font>");
        image1 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image1Button = new QToolButton;
        image1Button->setIconSize(resultSize);
        image1.load(":/images/snowman_" + colors.at(id) + ".png");
        image1Button->setIcon(QPixmap::fromImage(image1));

        layout->addWidget(image1Button, 0, 0);
        layout->addWidget(name1, 0 ,1);
        break;

    case 1:
        name2 = new QLabel("<font color=" + colors.at(id) +">" + *name + "</font>");
        image2 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image2Button = new QToolButton;
        image2Button->setIconSize(resultSize);
        image2.load(":/images/snowman_" + colors.at(id) + ".png");
        image2Button->setIcon(QPixmap::fromImage(image2));

        layout->addWidget(image2Button, 1, 0);
        layout->addWidget(name2, 1 ,1);
        break;

    case 2:
        name3 = new QLabel("<font color=" + colors.at(id) +">" + *name + "</font>");
        image3 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image3Button = new QToolButton;
        image3Button->setIconSize(resultSize);
        image3.load(":/images/snowman_" + colors.at(id) + ".png");
        image3Button->setIcon(QPixmap::fromImage(image3));

        layout->addWidget(image3Button, 2, 0);
        layout->addWidget(name3, 2 ,1);
        break;

    case 3:
        name4 = new QLabel("<font color=" + colors.at(id) +">" + *name + "</font>");
        image4 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image4Button = new QToolButton;
        image4Button->setIconSize(resultSize);
        image4.load(":/images/snowman_" + colors.at(id) + ".png");
        image4Button->setIcon(QPixmap::fromImage(image4));

        layout->addWidget(image4Button, 3, 0);
        layout->addWidget(name4, 3 ,1);
        break;

    case 4:
        name5 = new QLabel("<font color=" + colors.at(id) +">" + *name + "</font>");
        image5 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image5Button = new QToolButton;
        image5Button->setIconSize(resultSize);
        image5.load(":/images/snowman_" + colors.at(id) + ".png");
        image5Button->setIcon(QPixmap::fromImage(image5));

        layout->addWidget(image5Button, 4, 0);
        layout->addWidget(name5, 4 ,1);
        break;

    case 5:
        name6 = new QLabel("<font color=" + colors.at(id) +">" + *name + "</font>");
        image6 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image6Button = new QToolButton;
        image6Button->setIconSize(resultSize);
        image6.load(":/images/snowman_" + colors.at(id) + ".png");
        image6Button->setIcon(QPixmap::fromImage(image6));

        layout->addWidget(image6Button, 5, 0);
        layout->addWidget(name6, 5, 1);;
        break;
    }
}
