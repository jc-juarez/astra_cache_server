// *************************************
// Astra Cache Server
// Utilities
// 'http_response.hh'
// Author: jcjuarez
// *************************************

#ifndef HTTP_RESPONSE_
#define HTTP_RESPONSE_

#include <memory>
#include <stdexcept>
#include "http_codes.hh"
#include <httpserver.hpp>
#include "../common/common.hh"

namespace astra
{
namespace server
{

//
// Utility function for encapsulating a custom HTTP response.
//
std::shared_ptr<httpserver::string_response>
create_http_response(
    const status_code p_status,
    const http::status_code p_http_status,
    const std::string& p_response_message = std::string());

} // namespace server.
} // namespace astra.

#endif