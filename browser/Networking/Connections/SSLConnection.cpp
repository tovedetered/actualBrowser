//
// Created by tobedetered on 4/16/24.
//

#include "SSLConnection.h"

SSLConnection::SSLConnection(const std::string &url,
                             boost::asio::io_context *io_context,
                             boost::asio::ssl::context *ctx) : Connection(url,
                                                                          io_context) {
    this->ctx = ctx;
}
void SSLConnection::setSocket() {
    activeSSLSocket = new boost::asio::ssl::stream<tcp::socket>(*io_context,
                                                                *ctx);
}
std::string SSLConnection::request(std::vector<std::string> headers) {
    return makeRequest(activeSSLSocket, headers);
}
