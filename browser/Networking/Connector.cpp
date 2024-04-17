//
// Created by tobedetered on 4/11/24.
//

#include "Connector.h"
#include "Connections/SSLConnection.h"


Connection *Connector::connect(std::string url) {
    delete activeURL;
    activeURL = new URL(url);
    spdlog::debug("Connecting to " +
                  activeURL->getHost() + " on " +
                  activeURL->getScheme());
    if (activeURL->getScheme() == "http") {
        httpConnect();
    } else if (activeURL->getScheme() == "https") {
        initHTTPS();
        httpsConnect();
    } else {
        spdlog::error("Scheme : " +
                      activeURL->getScheme() + ", not supported");
        exit(1);
    }
    spdlog::debug("Successfully connected to " +
                  activeURL->getHost() + " using " + activeURL->getScheme());
    return activeConnection;
}
void Connector::httpConnect() {
    activeConnection = new Connection(activeURL->getURL(), context);
    tcp::resolver resolver(*context);
    tcp::resolver::results_type endpoints =
            getEndpoints(resolver);
    activeConnection->setSocket();
    boost::asio::connect(*activeConnection->getSocket(), endpoints);
}

tcp::resolver::results_type Connector::getEndpoints(tcp::resolver &resolver) {
    if (activeConnection->getActiveURL()->getPort() == "0") {
        return resolver.resolve(activeConnection->getHost(),
                                activeConnection->getScheme());
    } else
        return resolver.resolve(activeConnection->getHost(),
                                activeConnection->getActiveURL()->getPort());
}


void Connector::httpsConnect() {
    activeConnection = new SSLConnection(activeURL->getURL(),
                                         context,
                                         sslContext);
    auto *activeConn =
            dynamic_cast<SSLConnection *>(activeConnection);
    activeConn->setSocket();
    //Normal Endpoint stuff
    tcp::resolver resolver(*context);
    tcp::resolver::results_type endpoints =
            getEndpoints(resolver);
    boost::asio::connect(activeConn->getSocket()->lowest_layer(),
                         endpoints);
    //---------------------
    //SSL handshaking
    activeConn->getSocket()->lowest_layer().set_option(tcp::no_delay(true));
    activeConn->getSocket()->set_verify_mode(ssl::verify_peer);
    activeConn->getSocket()->set_verify_callback(
            ssl::host_name_verification(
                    activeConn->getHost()));
    try {
        activeConn->getSocket()->handshake(ssl_socket::client);
    } catch (std::exception &e) {
        spdlog::error("SSL handshake of host: " + activeConn->getHost() + " failed." +
                      "Make the host-name is correctly typed in. Error: " + e.what());
        throw failed_handshake();
    }
    //---------------------
}
void Connector::initHTTPS() {
    //already initialized
    if (sslContext != nullptr) {
        return;
    }
    sslContext = new ssl::context(ssl::context::sslv23);
    sslContext->set_default_verify_paths();
    spdlog::debug("Successfully Initialized HTTPS");
}
