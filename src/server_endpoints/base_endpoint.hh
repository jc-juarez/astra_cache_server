// *************************************
// Astra Caching Server
// Server
// 'base_endpoint.hh'
// Author: jcjuarez
// *************************************

#ifndef BASE_ENDPOINT_
#define BASE_ENDPOINT_

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
    // Constructor. Initializes the base_endpoint class.
    //
    base_endpoint( /* Pass the caching_engine class handle here. */ );

private:

    //
    // Caching engine handle.
    //
    // std::shared_ptr<caching_engine> m_caching_engine;

};

} // namespace endpoints.
} // namespace server.
} // namespace astra.

#endif