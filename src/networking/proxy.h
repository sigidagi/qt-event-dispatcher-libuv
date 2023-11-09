#ifndef PROXY_H
#define PROXY_H

#include <string>

class Proxy {
  public:
    virtual void onMessageReceived(const std::string &message) = 0;
    virtual ~Proxy() = default;
};

#endif /* PROXY_H */
