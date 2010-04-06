#include "statusbar.h"

static const QSize resultSize(60, 60);

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent)
{

    name1 = new QLabel(tr(""));
    score1 = new QLabel(tr(""));
    round1 = new QLabel(tr(""));
    image1Button = new QToolButton;
    image1Button->setIconSize(resultSize);

    name2 = new QLabel(tr(""));
    score2 = new QLabel(tr(""));
    round2 = new QLabel(tr(""));
    image2Button = new QToolButton;
    image2Button->setIconSize(resultSize);

    name3 = new QLabel(tr(""));
    score3 = new QLabel(tr(""));
    round3 = new QLabel(tr(""));
    image3Button = new QToolButton;
    image3Button->setIconSize(resultSize);


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(image1Button, 0, 0, 3, 1);
    layout->addWidget(name1, 0 ,1);
    layout->addWidget(score1, 1, 1);
    layout->addWidget(round1, 2, 1);

    layout->addWidget(image2Button, 0, 2, 3, 1);
    layout->addWidget(name2, 0 ,3);
    layout->addWidget(score2, 1, 3);
    layout->addWidget(round2, 2, 3);

    layout->addWidget(image3Button, 0, 4, 3, 1);
    layout->addWidget(name3, 0 ,5);
    layout->addWidget(score3, 1, 5);
    layout->addWidget(round3, 2, 5);

    setLayout(layout);
}

void StatusBar::addPlayer(int id, QString &name, int color)
{
    switch(id)
    {
    case 0:
        name1->setText("<font color=\"black\">" + name + "</font>");
        score1->setText(tr("Score: 0"));
        round1->setText(tr("Rounds: mnoho"));
        image1 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image1.load(":/images/snowman_black.png");
        image1Button->setIcon(QPixmap::fromImage(image1));
        break;

    case 1:
        name2->setText("<font color=\"blue\">" + name + "</font>");
        score2->setText(tr("Score: 0"));
        round2->setText(tr("Rounds: 10"));
        image2 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image2.load(":/images/snowman_blue.png");
        image2Button->setIcon(QPixmap::fromImage(image2));
        break;

    case 2:
        name3->setText("<font color=\"red\">" + name + "</font>");
        score3->setText(tr("Score: 0"));
        round3->setText(tr("Rounds: 156"));
        image3 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image3.load(":/images/snowman_red.png");
        image3Button->setIcon(QPixmap::fromImage(image3));
        break;
    }

}

void StatusBar::changeScore(int id, int score)
{
    switch(id)
    {
    case 0:
        score1->setText(QString::number(score));
        break;

    case 1:
        score2->setText(QString::number(score));
        break;

    case 2:
        score3->setText(QString::number(score));
        break;
    }
}

void StatusBar::changeRound(int id, int round)
{
    switch(id)
    {
    case 0:
        round1->setText(QString::number(round));
        break;

    case 1:
        round2->setText(QString::number(round));
        break;

    case 2:
        round3->setText(QString::number(round));
        break;
    }
}
