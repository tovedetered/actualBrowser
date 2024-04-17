//
// Created by tobedetered on 4/16/24.
//

#include "Requester.h"
#define MAX_REDIRECT 5
std::string Requester::makeRequest(Connection *connection, int numRedirect) {
    if (numRedirect > MAX_REDIRECT) {
        spdlog::warn(&"Maximum number of redirects reached: "[numRedirect] +
                     std::string() + ". Aborting Connection");
        return {};
    }
    std::string result;
    try {
        result = connection->request(headers);
    } catch (std::exception &e) {
        spdlog::error(e.what() + std::string() +
                      " When requesting data from connection in Requester.cpp.");
        return std::string{};
    }

    if (size_t pos = result.find("redirect:"); pos != std::string::npos) {

        result = result.substr(pos + 9);
        spdlog::debug("Redirecting to: " + result);
        if (pos = result.find("http://"); pos != std::string::npos) {
            //If there is a full url
            Connection *newConnection = connector->connect(result);
            result = makeRequest(newConnection, numRedirect++);
        } else if (pos = result.find("https://"); pos != std::string::npos) {
            Connection *newConnection = connector->connect(result);
            result = makeRequest(newConnection, numRedirect++);
        } else {
            Connection *newConnection = connector->connect(
                    "https://" + connection->getHost() + result);
            result = makeRequest(newConnection, numRedirect++);
        }
        delete connection;
    }
    return result;
}
void Requester::initHeaders() {
    headers.emplace_back("User-Agent: Krambrowser\r\n");
    headers.emplace_back("Connection: Close\r\n");
}
