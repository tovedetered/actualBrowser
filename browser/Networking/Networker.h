//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_NETWORKER_H
#define ACTUALBROWSER_NETWORKER_H


#include "Connector.h"
#include "Requester.h"
#include <string>
class Networker {
public:
    Networker() {
        connector = new Connector;
        requestor = new Requester(connector);
    };
    ~Networker() {
        delete connector;
        delete requestor;
    }
    std::string makeRequest(std::string url);

private:
    Connector *connector;
    Requester *requestor;
};


#endif//ACTUALBROWSER_NETWORKER_H
