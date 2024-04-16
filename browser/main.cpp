//
// Created by tobedetered on 4/12/24.
//
#include <iostream>
#include "Connector.h"
int main(){
    Connector connector{};
    Connection * connection =
            connector.connect("https://browser.engineering/history.html");
    std::string response = connection->request();
    std::cout << response << std::endl;
    return 0;
}