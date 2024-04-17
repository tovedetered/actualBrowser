//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_GRAPHICALBROWSER_H
#define ACTUALBROWSER_GRAPHICALBROWSER_H
#include "../Browser.h"
#include "../Display/Graphical/GUIDisplay.h"
#include "structs.h"
class GraphicalBrowser : Browser {
public:
    GraphicalBrowser() {
        display = new GUIDisplay;
        scroll = 0;
    }
    void run() override;
    std::string load(std::string url);
    void computeLayout(const std::string &document);

private:
    void scrollDown();

    std::vector<charPos> display_list;
    int scroll;
};


#endif//ACTUALBROWSER_GRAPHICALBROWSER_H
