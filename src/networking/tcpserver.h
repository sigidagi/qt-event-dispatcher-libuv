#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "proxy.h"

class TcpServer {

  public:
    explicit TcpServer(unsigned int port, Proxy *proxy);
    void run();

  private:
    unsigned int port_;
    Proxy *proxy_;
    void dispatch(const std::string &message);
};

#endif /* TCPSERVER_H */
