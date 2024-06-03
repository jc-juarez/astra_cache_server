// *************************************
// Astra Cache Server
// Server
// 'base_endpoint.hh'
// Author: jcjuarez
// *************************************

#ifndef BASE_ENDPOINT_
#define BASE_ENDPOINT_

#include <string>
#include <memory>
#include "../http.hh"
#include <httpserver.hpp>

namespace astra
{
namespace server
{
namespace endpoints
{

//
// Base endpoint class for all server endpoints.
//
class base_endpoint : public httpserver::http_resource
{

public:

    //
    // Constructor.
    //
    base_endpoint(
        const character* p_url
        /* Pass the caching_engine class handle here. */ );

    //
    // Gets the URL associated to the endpoint.
    //
    const character*
    get_url() const;

private:

    //
    // Endpoint URL.
    //
    std::string m_url;

    //
    // Caching engine handle.
    //
    // std::shared_ptr<caching_engine> m_caching_engine;

};

} // namespace endpoints.
} // namespace server.
} // namespace astra.

#endif