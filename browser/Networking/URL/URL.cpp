//
// Created by tobedetered on 4/12/24.
//

#include "URL.h"
#define SCHEMEOFFSET 3
URL::URL(std::string url) {
    std::string tmpURL = url;
    size_t end_of_scheme = url.find(':');
    this->scheme = url.substr(0, end_of_scheme);//works
    url = url.substr(end_of_scheme + SCHEMEOFFSET);
    if (scheme != "http" && scheme != "https") {
        std::cerr << "ERROR: Unsupported Scheme Used: " + scheme << std::endl;
        exit(-1);
    }

    if (url.find('/') == std::string::npos) {
        url += '/';
    }

    size_t endOfHost = url.find('/');
    host = url.substr(0, endOfHost);
    //If there is a custom port
    if (host.find(':') != std::string::npos) {
        port = host.substr(host.find(':') + 1);
        host = host.substr(0, host.find(':'));
    } else
        port = "0";
    path = url.substr(endOfHost);
    active_status = {};
    this->url = tmpURL;
}
std::string URL::request(tcp::socket *socket) {
    //basic request
    std::string request = "GET " + path + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: Close\r\n\r\n";
    boost::asio::write(*socket, boost::asio::buffer(request));
    //STATUS LINE
    boost::asio::streambuf response;
    boost::asio::read_until(*socket, response, "\r\n");
    std::istream response_stream(&response);
    response_stream >> active_status.version;
    response_stream >> active_status.status;
    std::getline(response_stream, active_status.explanation);
    //-----------------------------------------------------------------------
    if (!response_stream || active_status.version.substr(0, 5) != "HTTP/") {
        std::cout << "Invalid response\n";
        throw std::invalid_argument("Invalid Response");
    }
    if (active_status.status != "200") {
        std::cout << "Response returned with active_status code " << active_status.status << "\n";
        throw std::invalid_argument("Invalid Status Code: " + active_status.status);
    }
    boost::asio::read_until(*socket, response, "\r\n\r\n");
    std::string line;
    while (std::getline(response_stream, line) && line != "\r") {
        std::pair<std::string, std::string> element;
        std::string header = line.substr(0, line.find(':'));
        for (auto c: header) {
            element.first.push_back(std::tolower(c));
        }
        std::string value = line.substr(line.find(':'));
        value.erase(remove_if(value.begin(), value.end(), isspace), value.end());
        for (auto c: value) {
            element.second.push_back(std::tolower(c));
        }
        headers.emplace(element);
    }
    assert(!headers.contains("transfer-encoding"));
    assert(!headers.contains("content-encoding"));

    if (response.size() > 0) {
        std::ostringstream ss;
        ss << &response;
        content = ss.str();
    }
    boost::system::error_code error;
    int count = 0;
    std::cout << "before loop" << std::endl;
    while (true) {
        std::cout << "before read" << std::endl;
        size_t len = boost::asio::read(*socket, response,
                                       boost::asio::transfer_at_least(1),
                                       error);
        if (len < 1) break;
        std::cout << "len: " << len << std::endl;
        std::ostringstream ss;
        ss << &response;
        content.append(ss.str());
        count++;
        std::cout << count << std::endl;
    }
    std::cout << "out of loop" << std::endl;
    if (error != boost::asio::error::eof)
        throw boost::system::system_error(error);
    return content;
}
const std::string &URL::getScheme() const {
    return scheme;
}
const std::string &URL::getHost() const {
    return host;
}
const std::string &URL::getPath() const {
    return path;
}
const std::string &URL::getURL() const {
    return url;
}

status &URL::getStatus() {
    return active_status;
}
std::unordered_map<std::string, std::string> &URL::getHeaders() {
    return headers;
}
std::string &URL::getContent() {
    return content;
}
const std::string &URL::getPort() const {
    return port;
}
