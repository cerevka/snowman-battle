#include "chatpanel.h"

ChatPanel::ChatPanel(QWidget *parent) :
    QWidget(parent)
{
    messageEdit = new QLineEdit;
    sendButton = new QPushButton(tr("Send"));
    layout = new QGridLayout;

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(messageEdit);
    buttonLayout->addWidget(sendButton);

    layout->addLayout(buttonLayout, 1000, 0, Qt::AlignBottom);
    number = 0;
    setLayout(layout);

    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
}

void ChatPanel::newMessage(QString *player, QString *message)
{
    QStringList list;
    list << "<" << *player << ">  " << *message;
    QString str = list.join("");

    QLabel *label = new QLabel(str);
    layout->addWidget(label, number++, 0, Qt::AlignTop);
}

void ChatPanel::sendMessage( void )
{
    QString mess = messageEdit->text();
    messageEdit->clear();
}
