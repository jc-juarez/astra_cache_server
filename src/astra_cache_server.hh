// *************************************
// Astra Cache Server
// Server
// 'astra_cache_server.hh'
// Author: jcjuarez
// *************************************

#ifndef ASTRA_CACHE_SERVER_
#define ASTRA_CACHE_SERVER_

#include <string>
#include <vector>
#include <memory>
#include "common.hh"

namespace astra
{

class system_configuration;

namespace server
{

class system_server;

}

//
// Main class for the astra cache server system.
//
class astra_cache_server
{

public:

    //
    // Constructor.
    //
    astra_cache_server(
        const system_configuration& p_system_configuration);

    //
    // Starts the astra caching server system.
    //
    status_code
    start_server();

    //
    // Main interface for starting the system.
    //
    static
    exit_code
    run(
        const std::vector<std::string>&& p_command_line_arguments);

    //
    // Main interface for initializing the system.
    //
    static
    status_code
    initialize(
        const std::vector<std::string>&& p_command_line_arguments);

private:

    //
    // System server main handle for handling HTTP requests.
    //
    std::unique_ptr<server::system_server> m_system_server;

};

} // namespace astra.

#endif