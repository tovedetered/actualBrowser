//
// Created by tobedetered on 4/11/24.
//

#ifndef ACTUALBROWSER_CONNECTOR_H
#define ACTUALBROWSER_CONNECTOR_H
#include "Connections/Connection.h"
#include "URL/URL.h"
#include <boost/asio/ssl.hpp>
#include <spdlog/spdlog.h>
#include <utility>

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;

class Connector {
public:
    Connector(){
        activeURL = nullptr;
        context = new boost::asio::io_context;
        sslContext = nullptr;
        activeConnection = nullptr;
    };
    Connection* connect(std::string url);

protected:
    URL* activeURL;
    boost::asio::io_context* context;
    Connection * activeConnection;
    void initHTTPS();
    void httpConnect();
    void httpsConnect();

    ssl::context *sslContext;
};


#endif//ACTUALBROWSER_CONNECTOR_H
