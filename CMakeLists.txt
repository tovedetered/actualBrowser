cmake_minimum_required(VERSION 3.28)
project(actualBrowser)

set(CMAKE_CXX_STANDARD 20)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS system regex)
find_package(spdlog REQUIRED)
find_package(OpenSSL REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})
    add_executable(daytime_client daytime_client/main.cpp)
    add_executable(daytime_server daytime_server/daytime_server.cpp)
    add_executable(browser browser/main.cpp browser/Connector.cpp browser/Connector.h
            browser/URL/URL.cpp
            browser/URL/URL.h
            browser/Connections/Connection.cpp
            browser/Connections/Connection.h
            browser/Connections/SSLConnection.cpp
            browser/Connections/SSLConnection.h
    )
    target_link_libraries(browser
            ${Boost_LIBRARIES}
            ${OPENSSL_LIBRARIES}
            spdlog::spdlog)
    target_link_libraries(daytime_client ${Boost_LIBRARIES} spdlog::spdlog)
    target_link_libraries(daytime_server ${Boost_LIBRARIES} spdlog::spdlog)
endif()