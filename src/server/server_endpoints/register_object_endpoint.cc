// *************************************
// Astra Cache Server
// Server
// 'register_object_endpoint.cc'
// Author: jcjuarez
// *************************************

#include "../http_response.hh"
#include "../../common/logger.hh"
#include "register_object_endpoint.hh"

namespace astra
{
namespace server
{
namespace endpoints
{

register_object_endpoint::register_object_endpoint( /* Pass the caching_engine class handle here. */ )
    : base_endpoint(c_url)
{}

std::shared_ptr<httpserver::http_response>
register_object_endpoint::render_POST(
    const httpserver::http_request& p_request)
{
    log_info_message("This is the request: {}.", p_request.get_path());

    return create_http_response(status::success, http::status_code::ok, "Returning data");
}

} // namespace endpoints.
} // namespace server.
} // namespace astra.