// *************************************
// Astra Cache Server
// Server
// 'base_endpoint.cc'
// Author: jcjuarez
// *************************************

#include "base_endpoint.hh"

namespace astra
{
namespace server
{
namespace endpoints
{

base_endpoint::base_endpoint(
    const character* p_url
     /* Pass the caching_engine class handle here. */ )
    : m_url(p_url)
{}

const character*
base_endpoint::get_url() const
{
    return m_url.c_str();
}

} // namespace endpoints.
} // namespace server.
} // namespace astra.