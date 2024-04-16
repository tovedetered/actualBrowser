//
// Created by tobedetered on 4/12/24.
//

#ifndef ACTUALBROWSER_URL_H
#define ACTUALBROWSER_URL_H

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <exception>
using boost::asio::ip::tcp;

struct status{
    std::string version;
    std::string status;
    std::string explanation;
};

class URL {
public:
    explicit URL(std::string url);

    virtual std::string request(tcp::socket *);
    const std::string &getScheme() const;
    const std::string &getHost() const;
    const std::string &getPath() const;
    const std::string &getURL() const;
    status &getStatus();
    std::unordered_map<std::string, std::string> &getHeaders();
    std::string &getContent();

private:
    std::string url;
    std::string scheme;
    std::string host;
    std::string path;

    status active_status;
    //Name, Value
    std::unordered_map<std::string, std::string> headers;

    std::string content;
};


#endif//ACTUALBROWSER_URL_H
