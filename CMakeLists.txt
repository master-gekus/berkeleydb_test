cmake_minimum_required(VERSION 3.3)

project(berkeleydb_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (MSVC)
    add_definitions(-DNOMINMAX)
endif()

add_subdirectory(berkeleydb_prebuilt)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} BerkeleyDB)
