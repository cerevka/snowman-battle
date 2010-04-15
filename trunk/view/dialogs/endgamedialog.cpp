#include "endgamedialog.h"

EndGameDialog::EndGameDialog(QWidget *parent)
    : QDialog(parent)
{

    colors << "black" << "red" << "blue" << "green" << "brown" << "yellow";
    ok = new QPushButton(tr("OK"));
    winnerLabel = new QLabel(tr("Winner"));

    layout = new QGridLayout;
    layout->addWidget(winnerLabel, 0, 0);
    layout->addWidget(ok, 3, 0);
    setLayout(layout);
    setFixedHeight(210);
    setFixedWidth(200);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
}

void EndGameDialog::winner(int id)
{
    QSize resultSize(80, 60);
    QString *name1 = Globals::mainWindow->getName(id);
    name = new QLabel("<font color=" + colors.at(id) +">" + *name1 + "</font>");
    image = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
    imageButton = new QToolButton;
    imageButton->setIconSize(resultSize);
    image.load(":/images/snowman_" + colors.at(id) + ".png");
    imageButton->setIcon(QPixmap::fromImage(image));

    layout->addWidget(imageButton, 1, 0);
    layout->addWidget(name, 1, 1);
}
