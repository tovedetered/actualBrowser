//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_GRAPHICALBROWSER_H
#define ACTUALBROWSER_GRAPHICALBROWSER_H
#include "../Browser.h"
#include "../Display/Graphical/RayGUIDisplay.h"

class GraphicalBrowser : Browser {
public:
    GraphicalBrowser() {
        display = new RayGUIDisplay;
    }
    void run() override;

private:
};


#endif//ACTUALBROWSER_GRAPHICALBROWSER_H