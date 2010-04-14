#include "statusbar.h"
#include "globals.h"

static const QSize resultSize(60, 50);

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent)
{
    colors << "black" << "red" << "blue" << "green" << "brown" << "yellow";
    score.resize(6);
    for(int i = 0; i < 6; i++)
        score[i] = 0;

    layout = new QGridLayout;
    setLayout(layout);
}

void StatusBar::addPlayer(int id)
{
    QString *name = Globals::mainWindow->getName(id);
    switch(id)
    {
    case 0:
        name1 = new QLabel("<font color=" + colors.at(id) +">" + *name + "</font>");
        score1 = new QLabel(tr("Score: 0"));
        round1 = new QLabel(tr("Rounds: mnoho"));
        image1 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image1Button = new QToolButton;
        image1Button->setIconSize(resultSize);
        image1.load(":/images/snowman_" + colors.at(id) + ".png");
        image1Button->setIcon(QPixmap::fromImage(image1));

        layout->addWidget(image1Button, 0, 0, 3, 1);
        layout->addWidget(name1, 0 ,1);
        layout->addWidget(score1, 1, 1);
        layout->addWidget(round1, 2, 1);
        break;

    case 1:
        name2 = new QLabel("<font color=" + colors.at(id) +">" + *name + "</font>");
        score2 = new QLabel(tr("Score: 0"));
        round2 = new QLabel(tr("Rounds: 10"));
        image2 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image2Button = new QToolButton;
        image2Button->setIconSize(resultSize);
        image2.load(":/images/snowman_" + colors.at(id) + ".png");
        image2Button->setIcon(QPixmap::fromImage(image2));

        layout->addWidget(image2Button, 0, 2, 3, 1);
        layout->addWidget(name2, 0 ,3);
        layout->addWidget(score2, 1, 3);
        layout->addWidget(round2, 2, 3);
        break;

    case 2:
        name3 = new QLabel("<font color=" + colors.at(id) +">" + *name + "</font>");
        score3 = new QLabel(tr("Score: 0"));
        round3 = new QLabel(tr("Rounds: 10"));
        image3 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image3Button = new QToolButton;
        image3Button->setIconSize(resultSize);
        image3.load(":/images/snowman_" + colors.at(id) + ".png");
        image3Button->setIcon(QPixmap::fromImage(image3));

        layout->addWidget(image3Button, 0, 4, 3, 1);
        layout->addWidget(name3, 0 ,5);
        layout->addWidget(score3, 1, 5);
        layout->addWidget(round3, 2, 5);
        break;

    case 3:
        name4 = new QLabel("<font color=" + colors.at(id) +">" + *name + "</font>");
        score4 = new QLabel(tr("Score: 0"));
        round4 = new QLabel(tr("Rounds: 10"));
        image4 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image4Button = new QToolButton;
        image4Button->setIconSize(resultSize);
        image4.load(":/images/snowman_" + colors.at(id) + ".png");
        image4Button->setIcon(QPixmap::fromImage(image4));

        layout->addWidget(image4Button, 0, 6, 3, 1);
        layout->addWidget(name4, 0 ,7);
        layout->addWidget(score4, 1, 7);
        layout->addWidget(round4, 2, 7);
        break;

    case 4:
        name5 = new QLabel("<font color=" + colors.at(id) +">" + *name + "</font>");
        score5 = new QLabel(tr("Score: 0"));
        round5 = new QLabel(tr("Rounds: 10"));
        image5 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image5Button = new QToolButton;
        image5Button->setIconSize(resultSize);
        image5.load(":/images/snowman_" + colors.at(id) + ".png");
        image5Button->setIcon(QPixmap::fromImage(image5));

        layout->addWidget(image5Button, 0, 8, 3, 1);
        layout->addWidget(name5, 0 ,9);
        layout->addWidget(score5, 1, 9);
        layout->addWidget(round5, 2, 9);
        break;

    case 5:
        name6 = new QLabel("<font color=" + colors.at(id) +">" + *name + "</font>");
        score6 = new QLabel(tr("Score: 0"));
        round6 = new QLabel(tr("Rounds: 10"));
        image6 = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        image6Button = new QToolButton;
        image6Button->setIconSize(resultSize);
        image6.load(":/images/snowman_" + colors.at(id) + ".png");
        image6Button->setIcon(QPixmap::fromImage(image6));

        layout->addWidget(image6Button, 0, 10, 3, 1);
        layout->addWidget(name6, 0 ,11);
        layout->addWidget(score6, 1, 11);
        layout->addWidget(round6, 2, 11);
        break;
    }

}

void StatusBar::changeScore(int id)
{
    score[id] = score.at(id) + 1;
    qDebug() << score[id];
    switch(id)
    {
    case 0:
        score1->setText("Score: " + QString::number(score[id]));
        break;

    case 1:
        score2->setText("Score: " + QString::number(score[id]));
        break;

    case 2:
        score3->setText("Score: " + QString::number(score[id]));
        break;

    case 3:
        score4->setText("Score: " + QString::number(score[id]));
        break;

    case 4:
        score5->setText("Score: " + QString::number(score[id]));
        break;

    case 5:
        score6->setText("Score: " + QString::number(score[id]));
        break;
    }
}

void StatusBar::changeRound(int id, int round)
{
    switch(id)
    {
    case 0:
        round1->setText("Rounds: " + QString::number(round));
        break;

    case 1:
        round2->setText("Rounds: " + QString::number(round));
        break;

    case 2:
        round3->setText("Rounds: " + QString::number(round));
        break;

    case 3:
        round4->setText("Rounds: " + QString::number(round));
        break;

    case 4:
        round5->setText("Rounds: " + QString::number(round));
        break;

    case 5:
        round6->setText("Rounds: " + QString::number(round));
        break;
    }
}
