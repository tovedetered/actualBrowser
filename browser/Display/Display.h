//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_DISPLAY_H
#define ACTUALBROWSER_DISPLAY_H


#include <string>
#include <unordered_map>

class Display {
public:
    virtual void display(const std::string &dom) = 0;
    virtual ~Display() = default;
    std::string lex(const std::string &dom);

protected:
    void initEntityMap();
    std::unordered_map<std::string, std::string> entityMap;
};


#endif//ACTUALBROWSER_DISPLAY_H
