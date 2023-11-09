#include "eventdispatcherlibuv.h"
#include "mainwindow.h"
#include <iostream>
#include <memory>

#include <QApplication>

#include "messagehandler.h"
#include "tcpserver.h"

int main(int argc, char **argv) {

    auto ev_dispatcher = new qtjs::EventDispatcherLibUv();
    QApplication::setEventDispatcher(ev_dispatcher);

    QApplication app(argc, argv);
    ev_dispatcher->setFinalise();
    QApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);

    MainWindow mainWindow;
    // []
    MessageHandler msgHandler(&mainWindow);
    TcpServer srv1(4242, &msgHandler);
    srv1.run();

    TcpServer srv2(5656, &msgHandler);
    srv2.run();

    mainWindow.show();
    return app.exec();
}
