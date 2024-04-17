//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_GUIDISPLAY_H
#define ACTUALBROWSER_GUIDISPLAY_H
#include "../Display.h"
#include <raygui.h>
#include <raylib.h>
#include <vector>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700
#include "../../Graphical/structs.h"
class GUIDisplay : public Display {
public:
    GUIDisplay();
    void display(const std::string &dom) override;
    ~GUIDisplay() override = default;
    void initDrawing();
    void drawCharbyChar(std::string lexedDom);
    static void drawDisplayListScroll(const std::vector<charPos> &display_list,
                                      int scrollPos);
    void endDrawing();
};


#endif//ACTUALBROWSER_GUIDISPLAY_H
