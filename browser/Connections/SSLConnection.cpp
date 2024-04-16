//
// Created by tobedetered on 4/16/24.
//

#include "SSLConnection.h"

SSLConnection::SSLConnection(const std::string &url,
                             boost::asio::io_context *io_context,
                             boost::asio::ssl::context *ctx) : Connection(url,
                                                                          io_context){
    this->ctx = ctx;
}
void SSLConnection::setSocket() {
    activeSSLSocket = new boost::asio::ssl::stream<tcp::socket>(*io_context,
                                                           *ctx);
}
std::string SSLConnection::request() {
    //basic request
    std::string request = "GET " + activeUrl->getPath() + " HTTP/1.1\r\n"
                          + "Host: " + activeUrl->getHost() + "\r\n"
                          + "Connection: Close\r\n\r\n";
    boost::asio::write(*activeSSLSocket, boost::asio::buffer(request));
    //STATUS LINE
    boost::asio::streambuf response;
    boost::asio::read_until(*activeSSLSocket, response, "\r\n");
    std::istream response_stream(&response);
    response_stream >> activeUrl->getStatus().version;
    response_stream >> activeUrl->getStatus().status;
    std::getline(response_stream, activeUrl->getStatus().explanation);
    //-----------------------------------------------------------------------
    if (!response_stream || activeUrl->getStatus().version.substr(0, 5) != "HTTP/")
    {
        std::cout << "Invalid response\n";
        throw std::invalid_argument("Invalid Response");
    }
    boost::asio::read_until(*activeSSLSocket, response, "\r\n\r\n");
    std::string line;
    while(std::getline(response_stream, line) && line != "\r"){
        std::pair<std::string, std::string> element;
        std::string header = line.substr(0,line.find(':'));
        for(auto c : header){
            element.first.push_back(std::tolower(c));
        }
        std::string value = line.substr(line.find(':') + 1);
        value.erase(remove_if(value.begin(), value.end(), isspace), value.end());
        for(auto c : value){
            element.second.push_back(std::tolower(c));
        }
        activeUrl->getHeaders().emplace(element);
    }
    assert(!activeUrl->getHeaders().contains("transfer-encoding"));
    assert(!activeUrl->getHeaders().contains("content-encoding"));
    if (std::stoi(activeUrl->getStatus().status) >= 300 && std::stoi(activeUrl->getStatus().status) < 400) {
        return std::string() + "redirect:" + activeUrl->getHeaders()["location"];
    }
    if(response.size() > 0){
        std::ostringstream ss;
        ss << &response;
        activeUrl->getContent() = ss.str();
    }
    boost::system::error_code error;
    int count = 0;
    while (true){
        size_t len = boost::asio::read(*activeSSLSocket, response,
                                       boost::asio::transfer_at_least(1),
                                       error);
        if(len < 1) break;
        std::ostringstream ss;
        ss << &response;
        activeUrl->getContent().append(ss.str());
        count ++;
        std::cout << count << std::endl;
    }
    if (error != boost::asio::error::eof)
        throw boost::system::system_error(error);
    return activeUrl->getContent();
}
