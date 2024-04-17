//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_BROWSER_H
#define ACTUALBROWSER_BROWSER_H


#include "Display/Display.h"
#include "Display/TextBased/BasicConsoleDisplay.h"
#include "Networking/Networker.h"
#include <string>
#include <utility>

class Browser {
public:
    Browser() {
        networker = new Networker;
        display = nullptr;
    };
    virtual ~Browser() {
        delete networker;
        delete display;
    }
    virtual void run() = 0;

protected:
    //Networking
    Networker *networker;
    //User Input


    //Displaying things
    Display *display;
};


#endif//ACTUALBROWSER_BROWSER_H
