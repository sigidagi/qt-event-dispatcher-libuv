#include "eventdispatcherlibuv.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char **argv) {

    QApplication::setEventDispatcher(new qtjs::EventDispatcherLibUv);
    QApplication app(argc, argv);

    QApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
