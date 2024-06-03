// *************************************
// Astra Cache Server
// Server
// 'default_endpoints.cc'
// Author: jcjuarez
// *************************************

#include "../http_response.hh"
#include "default_endpoints.hh"
#include "../../common/common.hh"

namespace astra
{
namespace server
{
namespace endpoints
{

std::shared_ptr<httpserver::http_response>
create_resource_not_found_response(
    const httpserver::http_request& request)
{
    return create_http_response(status::access_failure, http::status_code::not_found);
}

std::shared_ptr<httpserver::http_response>
create_method_not_allowed_response(
    const httpserver::http_request& request)
{
    return create_http_response(status::access_failure, http::status_code::method_not_allowed);
}

} // namespace endpoints.
} // namespace server.
} // namespace astra.