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
    explicit Requester(Connector* connector){
        this->connector = connector;
    };
    std::string makeRequest(Connection* connection, int numRedirect = 0);
private:
    Connector* connector;

};


#endif//ACTUALBROWSER_REQUESTER_H
