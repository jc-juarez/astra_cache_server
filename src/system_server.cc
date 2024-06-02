// *************************************
// Astra Cache Server
// Server
// 'system_server.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "system_server.hh"
#include "system_configuration.hh"
#include "server_endpoints/register_object_endpoint.hh"

namespace astra
{
namespace server
{

//
// Register system endpoint with the HTTP server macro.
//
#define register_system_endpoint(p_endpoint_name, p_http_method) \
    do \
    { \
    static endpoints::p_endpoint_name p_endpoint_name; \
    register_endpoint( \
        p_endpoint_name, \
        p_http_method, \
        p_endpoint_name.get_url()); \
    } \
    while (false)

system_server::system_server(
    const server_configuration& p_server_configuration)
{
    try
    {
        m_http_web_server = std::make_unique<httpserver::webserver>(httpserver::create_webserver(p_server_configuration.m_port_number));
    }
    catch (const std::exception& exception)
    {
        status_code status = status::http_server_initialization_failed;

        log_critical_message("Main system HTTP server initialization failed. Status={:#X}. Exception={}",
            status,
            exception.what());

        throw status_exception(status, "Failed to initialize the main HTTP server.");
    }
}

status_code
system_server::start()
{
    status_code status = set_system_endpoints();

    if (status::failed(status))
    {
        log_critical_message("Main system HTTP server startup failed. Status={:#X}.",
            status);
        
        return status;
    }

    try
    {
        m_http_web_server->start(true /* blocking */);
    }
    catch (const std::exception& exception)
    {
        status = status::http_server_startup_failed;

        log_critical_message("Main system HTTP server startup failed. Status={:#X}. Exception={}",
            status,
            exception.what());
    }

    return status;
}

status_code
system_server::set_system_endpoints()
{
    try
    {
        register_system_endpoint(register_object_endpoint, http::c_post_method);

        return status::success;
    }
    catch (const std::exception& exception)
    {
        status_code status = status::endpoints_setup_failed;

        log_critical_message("Failed to set the system server endpoints. Status={:#X}. Exception={}",
            status,
            exception.what());
        
        return status;
    }
}

} // namespace server.
} // namespace astra.