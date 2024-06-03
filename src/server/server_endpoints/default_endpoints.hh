// *************************************
// Astra Cache Server
// Server
// 'default_endpoints.hh'
// Author: jcjuarez
// *************************************

#ifndef DEFAULT_ENDPOINTS_
#define DEFAULT_ENDPOINTS_

#include <memory>
#include <httpserver.hpp>

namespace astra
{
namespace server
{
namespace endpoints
{

//
// Resource not found endpoint response construction.
//
std::shared_ptr<httpserver::http_response>
create_resource_not_found_response(
    const httpserver::http_request& request);

//
// HTTP Method not allowed endpoint response construction.
//
std::shared_ptr<httpserver::http_response>
create_method_not_allowed_response(
    const httpserver::http_request& request);

} // namespace endpoints.
} // namespace server.
} // namespace astra.

#endif