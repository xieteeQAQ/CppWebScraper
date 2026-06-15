cmake_minimum_required(VERSION 3.10)
project(WebScraper)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(WebScraper src/main.cpp
    src/request.cpp)
    
target_include_directories(WebScraper PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(WebScraper PRIVATE CURL::libcurl nlohmann_json::nlohmann_json)

set_target_properties(WebScraper PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)