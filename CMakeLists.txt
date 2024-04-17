cmake_minimum_required(VERSION 3.28)
project(actualBrowser)

set(CMAKE_CXX_STANDARD 20)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS system regex)
find_package(spdlog REQUIRED)
find_package(OpenSSL REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})
    add_executable(daytime_client daytime_client/main.cpp)
    add_executable(daytime_server daytime_server/daytime_server.cpp)
    add_executable(browser browser/main.cpp browser/Networking/Connector.cpp browser/Networking/Connector.h
            browser/Networking/URL/URL.cpp
            browser/Networking/URL/URL.h
            browser/Networking/Connections/Connection.cpp
            browser/Networking/Connections/Connection.h
            browser/Networking/Connections/SSLConnection.cpp
            browser/Networking/Connections/SSLConnection.h
            browser/Networking/Requester.cpp
            browser/Networking/Requester.h
            browser/Display/TextBased/BasicConsoleDisplay.cpp
            browser/Display/TextBased/BasicConsoleDisplay.h
            browser/Networking/Networker.cpp
            browser/Networking/Networker.h
            browser/Browser.cpp
            browser/Browser.h
            browser/Display/Display.cpp
            browser/Display/Display.h
            browser/BasicConsoleBrowser.cpp
            browser/BasicConsoleBrowser.h
            browser/Networking/Errors/failed_handshake.h
            browser/Display/Graphical/RayGUIDisplay.cpp
            browser/Display/Graphical/RayGUIDisplay.h
            browser/Graphical/GraphicalBrowser.cpp
            browser/Graphical/GraphicalBrowser.h
    )
    target_link_libraries(browser
            ${Boost_LIBRARIES}
            ${OPENSSL_LIBRARIES}
            spdlog::spdlog)
    target_link_libraries(daytime_client ${Boost_LIBRARIES} spdlog::spdlog)
    target_link_libraries(daytime_server ${Boost_LIBRARIES} spdlog::spdlog)
endif ()