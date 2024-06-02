# *************************************
# Astra Caching Server
# Build
# 'CMakeLists.txt'
# Author: jcjuarez
# *************************************

cmake_minimum_required(VERSION 3.0)

project(AstraCachingServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES
    src/main.cc
    src/system_server.cc
    src/status_exception.cc
    src/server_endpoints/base_endpoint.cc
    src/server_endpoints/register_object_endpoint.cc)

add_executable(astra ${SOURCE_FILES})

target_link_libraries(astra /usr/local/lib/libhttpserver.a microhttpd pthread)