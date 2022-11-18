cmake_minimum_required(VERSION 3.14)
project(mongusweeper VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_package(raylib QUIET)

include_directories(src)
include_directories(third_party)

file(GLOB_RECURSE cpp_files CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} ${cpp_files})

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -O2)
endif()
