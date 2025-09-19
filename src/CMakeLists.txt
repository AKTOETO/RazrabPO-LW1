cmake_minimum_required(VERSION 3.10)
project(calc CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp action.cpp)

target_link_libraries(${PROJECT_NAME} pqxx)
target_include_directories(${PROJECT_NAME} PUBLIC ../lib/pqxx/include)
