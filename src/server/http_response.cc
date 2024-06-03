// *************************************
// Astra Cache Server
// Utilities
// 'http_response.cc'
// Author: jcjuarez
// *************************************

#include <format>
#include "http_response.hh"

namespace astra
{
namespace server
{

std::shared_ptr<httpserver::string_response>
create_http_response(
    const status_code p_status,
    const http::status_code p_http_status,
    const std::string& p_response_message)
{
    const std::string formatted_response_message = std::format(
        R"({{"internal_status_code": {:#X}, "response_message": "{}"}})",
        p_status,
        p_response_message);

    return std::shared_ptr<httpserver::string_response>(std::make_shared<httpserver::string_response>(
        formatted_response_message,
        p_http_status));
}

} // namespace server.
} // namespace astra.