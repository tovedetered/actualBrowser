//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_BASICCONSOLEDISPLAY_H
#define ACTUALBROWSER_BASICCONSOLEDISPLAY_H
#include "../Display.h"
#include <iostream>
#include <string>
#include <unordered_map>


class BasicConsoleDisplay : public Display {
public:
    BasicConsoleDisplay() {
        initEntityMap();
    };
    void display(const std::string &dom) override;

public:
    void initEntityMap();
    std::unordered_map<std::string, std::string> entityMap;
};


#endif//ACTUALBROWSER_BASICCONSOLEDISPLAY_H
