#include "creategame.h"

CreateGame::CreateGame(QWidget *parent)
    : QDialog(parent)
{
    nicknameLabel = new QLabel(tr("Nickname:"));
    playersLabel = new QLabel(tr("Number of players:"));
    colorLabel = new QLabel(tr("Your color:"));
    okButton = new QPushButton(tr("Create game"));
    cancelButton = new QPushButton(tr("Cancel"));

    nickname = new QLineEdit;

    players = new QComboBox;
    players->addItem(tr("1"));
    players->addItem(tr("2"));
    players->addItem(tr("3"));
    players->addItem(tr("4"));
    players->addItem(tr("5"));
    players->addItem(tr("6"));

    color = new QComboBox;
    color->addItem(tr("Black"));
    color->addItem(tr("Red"));
    color->addItem(tr("Blue"));
    color->addItem(tr("Green"));
    color->addItem(tr("Pink"));
    color->addItem(tr("Yellow"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nicknameLabel, 0, 0);
    layout->addWidget(nickname, 0, 1);
    layout->addWidget(playersLabel, 1, 0);
    layout->addWidget(players, 1, 1);
    layout->addWidget(colorLabel, 2, 0);
    layout->addWidget(color, 2, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);

    setLayout(layout);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    setWindowTitle(tr("Create Game"));

}
