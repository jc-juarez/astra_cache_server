// *************************************
// Astra Caching Server
// Utilities
// 'status_exception.hh'
// Author: jcjuarez
// *************************************

#ifndef STATUS_EXCEPTION_
#define STATUS_EXCEPTION_

#include <stdexcept>
#include "status.hh"
#include "utilities.hh"

namespace astra
{

//
// Exception wrapper class for status codes.
//
class status_exception : std::runtime_error
{

public:

    //
    // Constructor. Initializes the status_exception class.
    //
    status_exception(
        const status_code p_status,
        const character* p_message);

    //
    // Retrieves the status code of the exception.
    //
    status_code
    get_status() const;

private:

    //
    // Status code for the generated exception.
    //
    status_code m_status;

};

} // namespace astra.

#endif