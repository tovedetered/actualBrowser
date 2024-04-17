//
// Created by tobedetered on 4/16/24.
//

#ifndef ACTUALBROWSER_FAILED_HANDSHAKE_H
#define ACTUALBROWSER_FAILED_HANDSHAKE_H
#include <exception>

class failed_handshake : public std::exception {
public:
    [[nodiscard]] const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "SSL Handshake Failed";
    }
};


#endif//ACTUALBROWSER_FAILED_HANDSHAKE_H
