// *************************************
// Astra Caching Server
// Server
// 'register_object_endpoint.cc'
// Author: jcjuarez
// *************************************

#include "register_object_endpoint.hh"
#include <iostream> // delete.

namespace astra
{
namespace server
{
namespace endpoints
{

register_object_endpoint::register_object_endpoint( /* Pass the caching_engine class handle here. */ )
{}

std::shared_ptr<httpserver::http_response>
register_object_endpoint::render_POST(
    const httpserver::http_request& p_request)
{
    std::cout << p_request.get_path() << std::endl;
    return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("hello", http::status_code::ok, "text/plain")); 
}

} // namespace endpoints.
} // namespace server.
} // namespace astra.