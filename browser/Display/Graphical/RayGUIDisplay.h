//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_RAYGUIDISPLAY_H
#define ACTUALBROWSER_RAYGUIDISPLAY_H
#include "../Display.h"
#include <raygui.h>

class RayGUIDisplay : public Display {
public:
    void display(const std::string &dom) override;
    ~RayGUIDisplay() override = default;
    void initDrawing();
    void endDrawing();
};


#endif//ACTUALBROWSER_RAYGUIDISPLAY_H
