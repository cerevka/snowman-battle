#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>
#include <QtGui>

class QLabel;
class QToolButton;

/**
  * Trida reprezentujici statusbar
  */
class StatusBar : public QWidget
{
Q_OBJECT
public:

    /**
      * Vytvori statusbar
      */
    explicit StatusBar(QWidget *parent = 0);

public slots:
    /**
      * Prida na statusbar noveho hrace
      * @param id id hrace
      */
    void addPlayer(int id);

    /**
      * Zmeni score hrace
      * @param id id hrace
      */
    void changeScore(int id);

    /**
      * Zmeni pocet naboju
      * @param id id hrace
      * @param round pocet naboju
      */
    void changeRound(int id, int round);

private:

    QGridLayout *layout;

    QLabel *name1;
    QLabel *score1;
    QLabel *round1;
    QToolButton *image1Button;
    QImage image1;

    QLabel *name2;
    QLabel *score2;
    QLabel *round2;
    QToolButton *image2Button;
    QImage image2;

    QLabel *name3;
    QLabel *score3;
    QLabel *round3;
    QToolButton *image3Button;
    QImage image3;

    QLabel *name4;
    QLabel *score4;
    QLabel *round4;
    QToolButton *image4Button;
    QImage image4;

    QLabel *name5;
    QLabel *score5;
    QLabel *round5;
    QToolButton *image5Button;
    QImage image5;

    QLabel *name6;
    QLabel *score6;
    QLabel *round6;
    QToolButton *image6Button;
    QImage image6;

    QStringList colors;
    QVector<int> score;

};

#endif // STATUSBAR_H
