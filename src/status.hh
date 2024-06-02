// *************************************
// Astra Caching Server
// Utilities
// 'status.hh'
// Author: jcjuarez
// *************************************

#ifndef STATUS_
#define STATUS_

namespace astra
{

//
// Status code type alias.
//
using status_code = unsigned int;

//
// Status class for indicating errors across the system.
//
class status
{

    //
    // Static class.
    //
    status() = delete;

public:

    //
    // Determines whether a given status is considered as failure.
    //
    inline static
    bool
    failed(
        const status_code p_status_code)
    {
        return static_cast<int>(p_status_code) < 0;
    }

    //
    // Determines whether a given status is considered as success.
    //
    inline static
    bool
    succeeded(
        const status_code& p_status_code)
    {
        return p_status_code == success;
    }

    //
    // Determines whether a given status is the same as another status.
    //
    inline static
    bool
    is_same(
        const status_code& p_status_code_left,
        const status_code& p_status_code_right)
    {
        return p_status_code_left == p_status_code_right;
    }

    //
    // Determines whether a given status is not the same as another status.
    //
    inline static
    bool
    is_not_same(
        const status_code& p_status_code_left,
        const status_code& p_status_code_right)
    {
        return p_status_code_left != p_status_code_right;
    }

    //
    // Status code definition macro.
    //
    #define status_code_definition(p_status_code_name, p_status_code_value) static constexpr status_code p_status_code_name = p_status_code_value

    //
    // Operation succeeded.
    //
    status_code_definition(success, 0x0'0000000);

    //
    // Generic operation failed.
    //
    status_code_definition(fail, 0x8'0000000);

    //
    // Failure to initialize the main HTTP server.
    //
    status_code_definition(http_server_initialization_failed, 0x8'0000001);

    //
    // Failure to start the main HTTP server.
    //
    status_code_definition(http_server_startup_failed, 0x8'0000002);

};

} // namespace astra.

#endif