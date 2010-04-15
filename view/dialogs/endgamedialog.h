#ifndef ENDGAMEDIALOG_H
#define ENDGAMEDIALOG_H

#include <QDialog>
#include <QtGui>
#include "globals.h"

class QLabel;
class QToolButton;
class QPushButton;

class EndGameDialog : public QDialog
{
    Q_OBJECT

public:
    /**
      * Dialog zobrazeny po konci hry
      */
    EndGameDialog(QWidget *parent=0);

public slots:

    /**
      * Zobrazi hrace, ktery vyhral
      * @param id id hrace
      */
    void winner(int id);

private:
    QGridLayout *layout;

    QLabel *winnerLabel;
    QLabel *name;
    QToolButton *imageButton;
    QImage image;
    QPushButton *ok;

    QStringList colors;
};

#endif // ENDGAMEDIALOG_H
