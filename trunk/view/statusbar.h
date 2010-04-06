#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>
#include <QtGui>

class QLabel;
class QToolButton;

class StatusBar : public QWidget
{
Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = 0);
    void addPlayer(int id, QString &name, int color);
    void changeScore(int id, int score);
    void changeRound(int id, int round);

private:

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



};

#endif // STATUSBAR_H
