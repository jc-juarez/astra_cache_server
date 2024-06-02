// *************************************
// Astra Cache Server
// Server
// 'system_server.hh'
// Author: jcjuarez
// *************************************

#ifndef SYSTEM_SERVER_
#define SYSTEM_SERVER_

#include <memory>
#include "common.hh"
#include <httpserver.hpp>

namespace astra
{

struct server_configuration;

namespace server
{

//
// Main server class for handling incoming HTTP caching requests.
//
class system_server
{

public:

    //
    // Constructor.
    //
    system_server(
        const server_configuration& p_server_configuration);

    //
    // Starts the system server.
    //
    status_code
    start();

private:

    //
    // Registers an endpoint with the internal HTTP server.
    //
    template <typename T> 
    void
    register_endpoint(
        T& p_endpoint,
        const character* p_http_method,
        const character* p_endpoint_url)
    {
        p_endpoint.disallow_all();

        p_endpoint.set_allowing(
            p_http_method,
            true /* allowed */);

        m_http_web_server->register_resource(
            p_endpoint_url,
            &p_endpoint);
    }

    //
    // Binds and sets the endpoints for receiving incoming HTTP caching requests.
    //
    status_code
    set_system_endpoints();

    //
    // Exclusive handle to the internal HTTP server.
    //
    std::unique_ptr<httpserver::webserver> m_http_web_server;

};

} // namespace server.
} // namespace astra.

#endif