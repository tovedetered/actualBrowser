//
// Created by tobedetered on 4/16/24.
//

#include "BasicConsoleBrowser.h"

BasicConsoleBrowser::BasicConsoleBrowser() {
    display = new BasicConsoleDisplay;
}
void BasicConsoleBrowser::run() {
    while (true) {
        std::cout << "-- KramBrowser --" << std::endl;
        //Get Input
        std::string input;
        std::getline(std::cin, input);

        //-----------------------

        //Update

        user_action action = getAction(input);
        std::string buffer;
        switch (action) {
            case QUIT:
                goto out_of_loop;
            case GET:
                buffer = networker->makeRequest(input.substr(input.find(' ') + 1));
                break;
            default:
                std::cerr << "USAGE: \n"
                          << "QUIT -- quits \n"
                          << "GET -- gets a url to display" << std::endl;
        }
        //-----------------------

        //Display
        display->display(buffer);
    }
out_of_loop:
    int i = 0;
}
bool BasicConsoleBrowser::wantToQuit(std::string input) {
    if (input == "q" || input == "quit" || input == "QUIT") return true;
    return false;
}
user_action BasicConsoleBrowser::getAction(std::string input) {
    if (wantToQuit(input)) return QUIT;
    std::string commandBuffer;
    for (int i = 0; i < 3; i++) {
        commandBuffer.push_back(input[i]);
    }
    if (commandBuffer == "get" || commandBuffer == "GET" || commandBuffer == "Get")
        return GET;
    return INVALID;
}
