//
// Created by tobedetered on 4/12/24.
//

#ifndef ACTUALBROWSER_CONNECTION_H
#define ACTUALBROWSER_CONNECTION_H
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <boost/asio.hpp>
#include <utility>

#include "../URL/URL.h"
using boost::asio::ip::tcp;

class Connection {
public:
    explicit Connection(std::string url, boost::asio::io_context* context){
        io_context = context;
        this->url = url;
        activeUrl = new URL(url);
        activeSocket = nullptr;
    }
    virtual ~Connection(){
        delete activeUrl;
        if(activeSocket){
            activeSocket->close();
        }
        delete activeSocket;
    }
    int setUrl(std::string newURL){
        URL tmp(std::move(newURL));
        if(tmp.getScheme() == activeUrl->getScheme() &&
            tmp.getHost() == activeUrl->getHost()){
            return 0;
        }
        else{
            return -1;
        }
    }
    virtual void setSocket(){
        activeSocket = new tcp::socket(*io_context);
    }
    std::string getScheme(){
        return activeUrl->getScheme();
    }
    std::string getHost(){
        return activeUrl->getHost();
    }
    tcp::socket* getSocket(){
        return activeSocket;
    }
    virtual std::string request();
protected:

    std::string url;
    URL* activeUrl;
    boost::asio::io_context *io_context;
    tcp::socket *activeSocket{};
    //Add socket data here and pass to url's request
};


#endif//ACTUALBROWSER_CONNECTION_H
