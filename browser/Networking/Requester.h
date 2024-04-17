//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_REQUESTER_H
#define ACTUALBROWSER_REQUESTER_H


#include "Connections/Connection.h"
#include "Connector.h"
#include <string>
class Requester {
public:
    explicit Requester(Connector *connector) {
        this->connector = connector;
        initHeaders();
    };
    std::string makeRequest(Connection *connection, int numRedirect = 0);
    void initHeaders();

private:
    Connector *connector;
    std::vector<std::string> headers;
};


#endif//ACTUALBROWSER_REQUESTER_H
