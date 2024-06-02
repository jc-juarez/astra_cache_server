// *************************************
// Astra Cache Server
// Utilities
// 'http.hh'
// Author: jcjuarez
// *************************************

#ifndef HTTP_
#define HTTP_

#include "common.hh"

namespace astra
{
namespace server
{

//
// Container class for HTTP-related information.
//
class http
{

    //
    // Static class.
    //
    http() = delete;

public:

    //
    // HTTP POST method string literal.
    //
    static constexpr const character* c_post_method = "POST";

    //
    // HTTP GET method string literal.
    //
    static constexpr const character* c_get_method = "GET";

    //
    // HTTP DELETE method string literal.
    //
    static constexpr const character* c_delete_method = "DELETE";

    //
    // Enum for encapsulating standard HTTP error codes.
    //
    enum status_code
    {
        ok = 200,
        internal_server_error = 500
    };

};

} // namespace server.
} // namespace astra.

#endif