#include "tcpserver.h"
#include <iostream>
#include <uvw.hpp>

TcpServer::TcpServer(unsigned int port, Proxy *proxy) : port_(port), proxy_(proxy) {}

void TcpServer::run() {
    auto uvwLoop = uvw::loop::create(uv_default_loop());

    auto tcp = uvwLoop->resource<uvw::tcp_handle>();

    // listen for tcp events;
    tcp->on<uvw::listen_event>([this](const uvw::listen_event &, uvw::tcp_handle &srv) {
        std::shared_ptr<uvw::tcp_handle> client = srv.parent().resource<uvw::tcp_handle>();

        client->on<uvw::close_event>(
            [ptr = srv.shared_from_this()](const uvw::close_event &, uvw::tcp_handle &) { ptr->close(); });
        client->on<uvw::end_event>([](const uvw::end_event &, uvw::tcp_handle &client) { client.close(); });

        client->on<uvw::data_event>([this](const uvw::data_event &data, uvw::tcp_handle &) {
            std::cout << "data on port: " << this->port_ << ", length: " << data.length << "\n";
            /*
             *for (size_t i = 0; i < data.length; ++i) {
             *    std::cout << data.data[i];
             *}
             */

            std::string name = std::string(data.data.get(), data.length);
            std::cout << "message: " << name << "\n";
            this->dispatch(name);
        });

        srv.accept(*client);
        client->read();
    });

    std::cout << "Started tcp server on local port: " << port_ << "\n";
    tcp->bind("127.0.0.1", port_);
    tcp->listen();
}

void TcpServer::dispatch(const std::string &message) {
    if (proxy_) {
        proxy_->onMessageReceived(message);
    }
}
