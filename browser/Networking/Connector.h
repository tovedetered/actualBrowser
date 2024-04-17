//
// Created by tobedetered on 4/11/24.
//

#ifndef ACTUALBROWSER_CONNECTOR_H
#define ACTUALBROWSER_CONNECTOR_H
#include "Connections/Connection.h"
#include "Errors/failed_handshake.h"
#include "URL/URL.h"
#include <boost/asio/ssl.hpp>
#include <spdlog/spdlog.h>
#include <utility>


using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;

class Connector {
public:
    Connector() {
        activeURL = nullptr;
        context = new boost::asio::io_context;
        sslContext = nullptr;
        activeConnection = nullptr;
    };
    Connection *connect(std::string url);
    ~Connector() {
        delete context;
        context = nullptr;
        delete sslContext;
        sslContext = nullptr;
        delete activeURL;
        activeURL = nullptr;
        delete activeConnection;
        activeConnection = nullptr;
    }

protected:
    URL *activeURL;
    boost::asio::io_context *context;
    Connection *activeConnection;
    void initHTTPS();
    void httpConnect();
    void httpsConnect();
    tcp::resolver::results_type getEndpoints(tcp::resolver &resolver);

    ssl::context *sslContext;
};


#endif//ACTUALBROWSER_CONNECTOR_H
