// *************************************
// Astra Caching Server
// Server
// 'system_server.cc'
// Author: jcjuarez
// *************************************

#include "system_server.hh"
#include "status_exception.hh"
#include <iostream> // delete.
#include "server_endpoints/register_object_endpoint.hh"

namespace astra
{
namespace server
{

system_server::system_server()
{
    try
    {
        m_http_web_server = std::make_unique<httpserver::webserver>(httpserver::create_webserver(8080));
    }
    catch (const std::exception& exception)
    {
        // Log exception error.
        throw status_exception(status::http_server_initialization_failed, "Failed to initialize the main HTTP server.");
    }
}

status_code
system_server::start()
{
    status_code status = set_system_endpoints();

    try
    {
        m_http_web_server->start(true /* blocking */);
    }
    catch (const std::exception& exception)
    {
        // Log exception error.
        std::cout << "Catched exception" << std::endl;
    }

    return status;
}

status_code
system_server::set_system_endpoints()
{
    //
    // Register an object with the caching server.
    //
    static endpoints::register_object_endpoint register_object_endpoint;

    register_endpoint(
        register_object_endpoint,
        http::c_post_method,
        endpoints::register_object_endpoint::c_url);

    return status::success; // catch errors with try catch.
}

} // namespace server.
} // namespace astra.