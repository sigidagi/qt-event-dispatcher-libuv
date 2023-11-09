#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

// Qt MessageHandler.h
#include "mainwindow.h"
#include "proxy.h"
#include <string>

class MainWindow;

class MessageHandler : public Proxy {
  public:
    MessageHandler(MainWindow *window);
    void onMessageReceived(const std::string &message) override;

  private:
    MainWindow *window_;
};

#endif /* MESSAGEHANDLER_H */
