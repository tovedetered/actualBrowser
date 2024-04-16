//
// Created by tobedetered on 4/11/24.
//
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
std::string makeDayTimeString();
int main(){
    try{
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context,
                               tcp::endpoint(tcp::v4(), 13));
        for(;;){
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::string message = makeDayTimeString();
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
std::string makeDayTimeString(){
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}