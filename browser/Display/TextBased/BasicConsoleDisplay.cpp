//
// Created by tobedetered on 4/16/24.
//

#include "BasicConsoleDisplay.h"
void BasicConsoleDisplay::display(const std::string &dom) {
    std::cout << lex(dom);
    std::cout << std::endl;
}