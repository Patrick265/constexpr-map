cmake_minimum_required(VERSION 3.16)


project(utility VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME}-demo main.cpp)

target_include_directories( ${PROJECT_NAME}-demo PRIVATE include/)
target_compile_features(    ${PROJECT_NAME}-demo PRIVATE cxx_std_20)
target_compile_options(     ${PROJECT_NAME}-demo PRIVATE -Wall -Wextra -Werror -fdiagnostics-color=always -Wno-unused-variable -Wno-unused-parameter)