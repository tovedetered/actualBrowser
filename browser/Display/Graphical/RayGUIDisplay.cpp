//
// Created by tobedetered on 4/16/24.
//

#include "RayGUIDisplay.h"
void RayGUIDisplay::display(const std::string &dom) {
}
void RayGUIDisplay::initDrawing() {
    BeginDrawing();
    ClearBackground(GetColor(
            GuiGetStyle(
                    DEFAULT,
                    BACKGROUND_COLOR)));
}

void RayGUIDisplay::endDrawing() {
    EndDrawing();
}
