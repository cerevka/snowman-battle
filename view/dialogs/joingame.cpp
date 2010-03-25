#include "joingame.h"

JoinGame::JoinGame(QWidget *parent)
    : QDialog(parent)
{
    nicknameLabel = new QLabel(tr("Nickname:"));
    addressLabel = new QLabel(tr("Address of server:"));
    portLabel = new QLabel(tr("Port:"));
    colorLabel = new QLabel(tr("Your color:"));
    okButton = new QPushButton(tr("Join game"));
    cancelButton = new QPushButton(tr("Cancel"));

    nickname = new QLineEdit;
    address = new QLineEdit;
    port = new QLineEdit;

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
    layout->addWidget(addressLabel, 1, 0);
    layout->addWidget(address, 1, 1);
    layout->addWidget(portLabel, 2, 0);
    layout->addWidget(port, 2, 1);
    layout->addWidget(colorLabel, 3, 0);
    layout->addWidget(color, 3, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);

    setLayout(layout);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    setWindowTitle(tr("Create Game"));

}
