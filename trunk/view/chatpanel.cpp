#include "chatpanel.h"
#include "globals.h"

ChatPanel::ChatPanel(QWidget *parent) :
    QWidget(parent)
{    
    messageEdit = new QLineEdit;
    sendButton = new QPushButton(tr("Send"));
    layout = new QGridLayout;

    chatMess = new QTextEdit(this);
    chatMess->setReadOnly(true);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(messageEdit);
    buttonLayout->addWidget(sendButton);

    layout->addWidget(chatMess, 0, 0);
    layout->addLayout(buttonLayout, 1, 0, Qt::AlignBottom);
    number = 0;
    setLayout(layout);

    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(this, SIGNAL(sendMessage(int, QString*)), Globals::packetCreator, SLOT(sendChatMessage(int, QString*)));
}

void ChatPanel::newMessage(int id, QString *message)
{
    QStringList list;
    QString *name = Globals::mainWindow->getName(id);
    list << "<" << *name << ">  " << *message;
    QString *str = new QString();
    *str = list.join("");

    qDebug() << "prijakta zprava";
    chatMess->append(*str);

}

void ChatPanel::sendMessage( void )
{
    QString mess = messageEdit->text();
    if(!mess.compare(""))
    {
        QMessageBox::warning(this, tr("Chat panel"),
                               tr("Please, insert your message."));
        return;
    }
    int id = Globals::network->getNetworkID();
    messageEdit->clear();

    emit sendMessage(id, &mess);
    qDebug() << "odeslana zprava";
}
