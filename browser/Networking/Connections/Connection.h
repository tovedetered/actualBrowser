//
// Created by tobedetered on 4/12/24.
//

#ifndef ACTUALBROWSER_CONNECTION_H
#define ACTUALBROWSER_CONNECTION_H
#include "../URL/URL.h"
#include <boost/asio.hpp>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <utility>

using boost::asio::ip::tcp;

class Connection {
public:
    explicit Connection(std::string url, boost::asio::io_context *context) {
        io_context = context;
        this->url = url;
        activeUrl = new URL(url);
        tcpSocket = nullptr;
    }
    virtual ~Connection() {
        delete activeUrl;
        if (tcpSocket) {
            tcpSocket->close();
        }
        delete tcpSocket;
    }
    int setUrl(std::string newURL) {
        URL tmp(std::move(newURL));
        if (tmp.getScheme() == activeUrl->getScheme() &&
            tmp.getHost() == activeUrl->getHost()) {
            return 0;
        } else {
            return -1;
        }
    }
    virtual void setSocket() {
        tcpSocket = new tcp::socket(*io_context);
    }
    std::string getScheme() {
        return activeUrl->getScheme();
    }
    std::string getHost() {
        return activeUrl->getHost();
    }
    URL *getActiveURL() {
        return activeUrl;
    }
    tcp::socket *getSocket() {
        return tcpSocket;
    }

    virtual std::string request(std::vector<std::string> headers);


protected:
    template<class socket>
    std::string makeRequest(socket *activeSocket,
                            std::vector<std::string> headers) {
        //basic request
        std::string request = "GET " + activeUrl->getPath() +
                              " HTTP/1.1\r\n" +
                              "Host: " + activeUrl->getHost() + "\r\n";
        for (const auto &header: headers) {
            //TODO: make sure headers are valid
            request.append(header);
        }
        request.append("\r\n");
        boost::asio::write(*activeSocket, boost::asio::buffer(request));
        //STATUS LINE
        boost::asio::streambuf response;
        boost::asio::read_until(*activeSocket, response, "\r\n");
        std::istream response_stream(&response);
        response_stream >> activeUrl->getStatus().version;
        response_stream >> activeUrl->getStatus().status;
        std::getline(response_stream, activeUrl->getStatus().explanation);
        //-----------------------------------------------------------------------
        if (!response_stream || activeUrl->getStatus().version.substr(0, 5) != "HTTP/") {
            std::cout << "Invalid response\n";
            throw std::invalid_argument("Invalid Response");
        }
        boost::asio::read_until(*activeSocket, response, "\r\n\r\n");
        std::string line;
        while (std::getline(response_stream, line) && line != "\r") {
            std::pair<std::string, std::string> element;
            std::string header = line.substr(0, line.find(':'));
            for (auto c: header) {
                element.first.push_back(std::tolower(c));
            }
            std::string value = line.substr(line.find(':') + 1);
            value.erase(remove_if(value.begin(), value.end(), isspace), value.end());
            for (auto c: value) {
                element.second.push_back(std::tolower(c));
            }
            activeUrl->getHeaders().emplace(element);
        }
        assert(!activeUrl->getHeaders().contains("transfer-encoding"));
        assert(!activeUrl->getHeaders().contains("content-encoding"));

        if (std::stoi(activeUrl->getStatus().status) >= 300 && std::stoi(activeUrl->getStatus().status) < 400) {
            return std::string() + "redirect:" + activeUrl->getHeaders()["location"];
        }

        if (response.size() > 0) {
            std::ostringstream ss;
            ss << &response;
            activeUrl->getContent() = ss.str();
        }
        boost::system::error_code error;
        int count = 0;
        while (true) {
            size_t len = boost::asio::read(*activeSocket, response,
                                           boost::asio::transfer_at_least(1),
                                           error);
            if (len < 1) break;
            std::ostringstream ss;
            ss << &response;
            activeUrl->getContent().append(ss.str());
            count++;
        }
        if (error != boost::asio::error::eof)
            throw boost::system::system_error(error);
        return activeUrl->getContent();
    };

    std::string url;
    URL *activeUrl;
    boost::asio::io_context *io_context;
    tcp::socket *tcpSocket{};
    //Add socket data here and pass to url's request
};


#endif//ACTUALBROWSER_CONNECTION_H
