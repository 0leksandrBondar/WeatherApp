cmake_minimum_required(VERSION 3.3)

project(WeatherApp)

include(FetchContent)

FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    GIT_TAG        v3.2
)

FetchContent_MakeAvailable(argparse)

FetchContent_Declare(
    curl
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG     curl-8_15_0
)

FetchContent_MakeAvailable(curl)


FetchContent_Declare(
    nlohmann
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG    v3.12.0
)

FetchContent_MakeAvailable(nlohmann)


add_executable(${PROJECT_NAME}
    Source/main.cpp
    Source/weatherdata.h Source/weatherdata.cpp
    Source/weatherfetcher.h Source/weatherfetcher.cpp
    Source/consoleprinter.h Source/consoleprinter.cpp
    Source/cache.h Source/cache.cpp
    Source/controller.h Source/controller.cpp
)


target_link_libraries(WeatherApp PUBLIC argparse CURL::libcurl nlohmann_json::nlohmann_json)
