// *************************************
// Astra Cache Server
// Server
// 'register_object_endpoint.hh'
// Author: jcjuarez
// *************************************

#ifndef REGISTER_OBJECT_ENDPOINT_
#define REGISTER_OBJECT_ENDPOINT_

#include "base_endpoint.hh"

namespace astra
{
namespace server
{
namespace endpoints
{

//
// Register object endpoint for caching binary streams of data.
//
class register_object_endpoint : public base_endpoint
{

public:

    //
    // Constructor.
    //
    register_object_endpoint( /* Pass the caching_engine class handle here. */ );

    //
    // Endpoint entry point.
    //
    virtual
    std::shared_ptr<httpserver::http_response>
    render_POST(
        const httpserver::http_request& p_request) override;

    //
    // Endpoint URL.
    //
    static constexpr const character* c_url = "/astra/register-object";

};

} // namespace endpoints.
} // namespace server.
} // namespace astra.

#endif