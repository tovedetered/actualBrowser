//
// Created by tobedetered on 4/12/24.
//
#include "BasicConsoleBrowser.h"
#include <spdlog/spdlog.h>
#define RAYGUI_IMPLEMENTATION
#include "../dependencies/raygui.h"
#undef RAYGUI_IMPLEMENTATION

int main() {
    spdlog::set_level(spdlog::level::debug);
    BasicConsoleBrowser browser;
    browser.run();
    return 0;
}