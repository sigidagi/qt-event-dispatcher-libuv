#include "eventdispatcherlibuv.h"

#include <QGuiApplication>

int main(int argc, char **argv) {

    QCoreApplication::setEventDispatcher(new qtjs::EventDispatcherLibUv);
    QCoreApplication app(argc, argv);

    // TODO
    // ...
    return app.exec();
}
