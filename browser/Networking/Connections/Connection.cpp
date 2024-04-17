//
// Created by tobedetered on 4/12/24.
//

#include "Connection.h"

std::string Connection::request(std::vector<std::string> headers) {
    return makeRequest(tcpSocket, std::move(headers));
}
