#include "eventdispatcherlibuv.h"
#include "mainwindow.h"
#include <iostream>
#include <memory>
#include <uvw.hpp>

#include <QApplication>

void listen(uvw::loop &loop) {
    std::shared_ptr<uvw::tcp_handle> tcp = loop.resource<uvw::tcp_handle>();

    tcp->on<uvw::listen_event>([](const uvw::listen_event &, uvw::tcp_handle &srv) {
        std::shared_ptr<uvw::tcp_handle> client = srv.parent().resource<uvw::tcp_handle>();

        client->on<uvw::close_event>(
            [ptr = srv.shared_from_this()](const uvw::close_event &, uvw::tcp_handle &) { ptr->close(); });
        client->on<uvw::end_event>([](const uvw::end_event &, uvw::tcp_handle &client) { client.close(); });

        srv.accept(*client);
        client->read();
    });

    std::cout << "Started tyo listen on local port: " << 4242 << "\n";

    tcp->bind("127.0.0.1", 4242);
    tcp->listen();
}

int main(int argc, char **argv) {

    auto ev_dispatcher = new qtjs::EventDispatcherLibUv();

    QApplication::setEventDispatcher(ev_dispatcher);

    QApplication app(argc, argv);
    ev_dispatcher->setFinalise();

    QApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
