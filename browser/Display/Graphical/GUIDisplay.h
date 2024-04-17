//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_GUIDISPLAY_H
#define ACTUALBROWSER_GUIDISPLAY_H
#include "../Display.h"
#include <raygui.h>
#include <raylib.h>

class GUIDisplay : public Display {
public:
    void display(const std::string &dom) override;
    ~GUIDisplay() override = default;
    void initDrawing();
    void endDrawing();
};


#endif//ACTUALBROWSER_GUIDISPLAY_H
