cmake_minimum_required(VERSION 3.28)
project(actualBrowser)

set(CMAKE_CXX_STANDARD 20)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS system regex)
find_package(spdlog REQUIRED)
find_package(OpenSSL REQUIRED)
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif ()
endif ()
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
            browser/Display/Graphical/GUIDisplay.cpp
            browser/Display/Graphical/GUIDisplay.h
            browser/Graphical/GraphicalBrowser.cpp
            browser/Graphical/GraphicalBrowser.h
            browser/Graphical/structs.h
    )
    target_link_libraries(browser
            ${Boost_LIBRARIES}
            ${OPENSSL_LIBRARIES}
            spdlog::spdlog
            raylib)
    target_link_libraries(daytime_client ${Boost_LIBRARIES} spdlog::spdlog)
    target_link_libraries(daytime_server ${Boost_LIBRARIES} spdlog::spdlog)
endif ()