#include "messagehandler.h"
#include <QDebug>

MessageHandler::MessageHandler(MainWindow *window) : window_(window) {}

void MessageHandler::onMessageReceived(const std::string &message) {
    qDebug() << "Message Received in Qt Application: " << QString::fromStdString(message);

    // Process the message in the Qt application as needed
    window_->teamMemberView()->getModel()->onTeamMemberAdded(QString::fromStdString(message));
}

