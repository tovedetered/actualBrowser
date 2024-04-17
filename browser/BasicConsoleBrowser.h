//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_BASICCONSOLEBROWSER_H
#define ACTUALBROWSER_BASICCONSOLEBROWSER_H
#include "Browser.h"
enum user_action {
    QUIT,
    GET,
    INVALID,
};


class BasicConsoleBrowser : Browser {
public:
    BasicConsoleBrowser();
    virtual ~BasicConsoleBrowser() override{

    };
    void run() override;

private:
    bool wantToQuit(std::string input);
    user_action getAction(std::string input);
};


#endif//ACTUALBROWSER_BASICCONSOLEBROWSER_H
