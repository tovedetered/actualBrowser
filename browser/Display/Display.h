//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_DISPLAY_H
#define ACTUALBROWSER_DISPLAY_H


#include <string>

class Display {
public:
    virtual void display(const std::string &dom) = 0;

    virtual ~Display() = default;
};


#endif//ACTUALBROWSER_DISPLAY_H
