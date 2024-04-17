//
// Created by tobedetered on 4/16/24.
//

#include "GraphicalBrowser.h"
void GraphicalBrowser::run() {
    GUIDisplay disp = *dynamic_cast<GUIDisplay *>(display);
    std::string buffer;
    bool submit = false;
    computeLayout("hello world");
    while (!WindowShouldClose()) {
        //Get Input
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125)) {
                buffer.push_back(static_cast<char>(key));
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (!buffer.empty())
                buffer.erase(buffer.end());
        }
        if (IsKeyPressed(KEY_ENTER)) {
            submit = true;
        }
        if (IsKeyPressed(KEY_DOWN)) {
            scrollDown();
        }
        //----------------------------------------

        //Update
        if (submit) {
            buffer = load(buffer);
            computeLayout(buffer);
            submit = false;
            buffer.clear();
        }
        //----------------------------------------

        //Draw
        disp.initDrawing();

        disp.drawDisplayListScroll(display_list, scroll);

        disp.endDrawing();
        //----------------------------------------
    }
    CloseWindow();
}
std::string GraphicalBrowser::load(std::string url) {
    std::string dom = networker->makeRequest(url);
    dom = display->lex(dom);
    return dom;
}
void GraphicalBrowser::computeLayout(const std::string &document) {
    display_list.clear();
    int HSTEP = 13;
    int VSTEP = 18;
    int cursor_x = HSTEP;
    int cursor_y = VSTEP;
    std::string line;
    for (auto c: document) {
        if (c == '\n') {
            cursor_y += VSTEP;
            cursor_x = HSTEP;
            continue;
        }
        display_list.push_back({cursor_x, cursor_y, c});
        cursor_x += HSTEP;
        if (cursor_x > WINDOW_WIDTH - HSTEP) {
            cursor_y += VSTEP;
            cursor_x = HSTEP;
        }
    }
}
std::vector<charPos> previousBuffer;

void GraphicalBrowser::scrollDown() {
    scroll += 18;
}
