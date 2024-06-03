// *************************************
// Astra Cache Server
// Utilities
// 'status_exception.cc'
// Author: jcjuarez
// *************************************

#include "status_exception.hh"

namespace astra
{

status_exception::status_exception(
    const status_code p_status,
    const character* p_message)
    : std::runtime_error(p_message),
      m_status(p_status)
{}

status_code
status_exception::get_status() const
{
    return m_status;
}

} // namespace astra.