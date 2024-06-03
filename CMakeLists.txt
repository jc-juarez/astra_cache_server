# *************************************
# Astra Cache Server
# Build
# 'CMakeLists.txt'
# Author: jcjuarez
# *************************************

cmake_minimum_required(VERSION 3.0)

project(AstraCachingServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES
    # Server components.
    src/server/main.cc
    src/server/system_server.cc
    src/server/astra_cache_server.cc
    src/server/server_endpoints/base_endpoint.cc
    src/server/server_endpoints/register_object_endpoint.cc

    # Cache components.

    # Common components.
    src/common/logger.cc
    src/common/timestamp.cc
    src/common/status_exception.cc
    src/common/system_configuration.cc
    src/common/filesystem_utilities.cc
    src/common/random_identifier_generator.cc
)

add_executable(astra ${SOURCE_FILES})

target_link_libraries(astra /usr/local/lib/libhttpserver.a microhttpd pthread)