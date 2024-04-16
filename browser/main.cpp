//
// Created by tobedetered on 4/12/24.
//
#include "Connector.h"
#include "Requester.h"
#include <iostream>
int main(){
    spdlog::set_level(spdlog::level::debug);
    Connector connector{};
    Connection * connection =
            connector.connect("https://browser.engineering/redirect3");
    Requester requestor(&connector);

    std::string response = requestor.makeRequest(connection);;
    std::cout << response << std::endl;
    return 0;
}