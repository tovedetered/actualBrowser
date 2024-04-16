//
// Created by tobedetered on 4/11/24.
//

#include "Connector.h"
#include "Connections/SSLConnection.h"


Connection* Connector::connect(std::string url) {
    activeURL = new URL(url);
    spdlog::debug("Connecting to "
                  + activeURL->getHost() + " on "
                  + activeURL->getScheme());
    if(activeURL->getScheme() == "http"){
        httpConnect();
    }
    else if(activeURL->getScheme() == "https"){
        initHTTPS();
        httpsConnect();
    }
    else{
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
            resolver.resolve(activeConnection->getHost(),
                             activeConnection->getScheme());
    activeConnection->setSocket();
    boost::asio::connect(*activeConnection->getSocket(), endpoints);
}

void Connector::httpsConnect() {
    activeConnection = new SSLConnection(activeURL->getURL(),
                                         context,
                                         sslContext);
    auto* activeConn =
            dynamic_cast<SSLConnection*>(activeConnection);
    activeConn->setSocket();
    //Normal Endpoint stuff
    tcp::resolver resolver(*context);
    tcp::resolver::results_type endpoints =
            resolver.resolve(activeConn->getHost(),
                             activeConn->getScheme());
    boost::asio::connect(activeConn->getSocket()->lowest_layer(),
                         endpoints);
    //---------------------
    //SSL handshaking
    activeConn->getSocket()->lowest_layer().
            set_option(tcp::no_delay(true));
    activeConn->getSocket()->set_verify_mode(ssl::verify_peer);
    activeConn->getSocket()->set_verify_callback(
            ssl::host_name_verification(
                    activeConn->getHost()));
    activeConn->getSocket()->handshake(ssl_socket::client);
    //---------------------
}
void Connector::initHTTPS() {
    //already initialized
    if(sslContext != nullptr){
        return;
    }
    sslContext = new ssl::context(ssl::context::sslv23);
    sslContext->set_default_verify_paths();
    spdlog::debug("Successfully Initialized HTTPS");
}
