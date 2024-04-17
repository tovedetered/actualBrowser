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
    SetTargetFPS(60);
}

void GUIDisplay::endDrawing() {
    EndDrawing();
}
void GUIDisplay::drawCharbyChar(std::string lexedDom) {
    int HSTEP = 13;
    int VSTEP = 18;
    int cursor_x = HSTEP;
    int cursor_y = VSTEP;
    std::string line;
    for (auto c: lexedDom) {
        DrawText(std::string(1, c).c_str(), cursor_x, cursor_y, 10, BLACK);
        cursor_x += HSTEP;
        if (cursor_x > WINDOW_WIDTH - HSTEP) {
            cursor_y += VSTEP;
            cursor_x = HSTEP;
        }
    }
}
GUIDisplay::GUIDisplay() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "KramBrowser");
}
void GUIDisplay::drawDisplayListScroll(const std::vector<charPos> &display_list,
                                       int scrollPos) {
    int lowerBound = scrollPos + GetScreenHeight();
    for (auto c: display_list) {
        if (c.y < scrollPos) {
            continue;
        }
        if (c.y > lowerBound) {
            break;
        }
        DrawText(std::string(1, c.c).c_str(),
                 c.x, c.y - scrollPos,
                 10, BLACK);
    }
}
