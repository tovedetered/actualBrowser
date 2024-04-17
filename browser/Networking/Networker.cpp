//
// Created by tobedetered on 4/16/24.
//

#include "Networker.h"
std::string Networker::makeRequest(std::string url) {
    try {
        Connection *connection =
                connector->connect(url);
        return requestor->makeRequest(connection);
    } catch (std::exception &e) {
        spdlog::error(e.what());
        return "\n";
    }
}
