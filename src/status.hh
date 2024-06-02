// *************************************
// Astra Cache Server
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

    //
    // Logger is not yet initialized.
    //
    status_code_definition(logger_not_initialized, 0x8'0000003);

    //
    // Logger is already initialized.
    //
    status_code_definition(logger_already_initialized, 0x8'0000004);

    //
    // Incorrect parameters.
    //
    status_code_definition(incorrect_parameters, 0x8'0000005);

    //
    // Failure to create a directory.
    //
    status_code_definition(directory_creation_failed, 0x8'0000006);
    
    //
    // Failure to retrieve an environment variable.
    //
    status_code_definition(environment_variable_access_failed, 0x8'0000007);

    //
    // Malformed commmand line arguments provided.
    //
    status_code_definition(malformed_command_line_arguments, 0x8'0000008);

    //
    // Provided configuration flag does not exist.
    //
    status_code_definition(configuration_flag_not_recognized, 0x8'0000009);
    
    //
    // Failed to write to a file.
    //
    status_code_definition(file_write_failed, 0x8'0000010);

    //
    // Failed to log to a file because incremental search reached its retry limit.
    //
    status_code_definition(logging_incremental_search_failed, 0x8'0000011);

};

} // namespace astra.

#endif