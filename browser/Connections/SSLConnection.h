//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_SSLCONNECTION_H
#define ACTUALBROWSER_SSLCONNECTION_H
#include "Connection.h"
#include <boost/asio/ssl.hpp>
typedef boost::asio::ssl::stream<tcp::socket> ssl_socket;

class SSLConnection : public Connection{
public:
    explicit SSLConnection(const std::string &url,
                           boost::asio::io_context *io_context,
                           boost::asio::ssl::context *ctx);
    void setSocket() override;
    ~SSLConnection(){
        activeSSLSocket->shutdown();
        delete activeSSLSocket;
    }
    //I know this hides it, it is by design
    ssl_socket * getSocket(){
        return activeSSLSocket;
    }
    std::string request() override;
private:
    ssl_socket *activeSSLSocket;
    boost::asio::ssl::context *ctx;
};


#endif//ACTUALBROWSER_SSLCONNECTION_H
