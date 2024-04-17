//
// Created by tobedetered on 4/16/24.
//

#include "GUIDisplay.h"
void GUIDisplay::display(const std::string &dom) {
}
void GUIDisplay::initDrawing() {
    BeginDrawing();
    ClearBackground(GetColor(
            GuiGetStyle(
                    DEFAULT,
                    BACKGROUND_COLOR)));
}

void GUIDisplay::endDrawing() {
    EndDrawing();
}
