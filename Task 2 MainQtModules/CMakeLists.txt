cmake_minimum_required(VERSION 3.14)

project(MainQtModules LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Network Sql REQUIRED)

add_executable(MainQtModules
  main.cpp
)

target_link_libraries(MainQtModules
    Qt6::Core
    Qt6::Network
    Qt6::Sql
)

