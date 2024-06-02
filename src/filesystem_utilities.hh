// *************************************
// Astra Cache Server
// Utilities
// 'filesystem_utilities.hh'
// Author: jcjuarez
// *************************************

#ifndef FILESYSTEM_UTILITIES_
#define FILESYSTEM_UTILITIES_

#include <string>
#include "common.hh"

namespace astra
{
namespace utilities
{

//
// Filesystem utilities container class
//
class filesystem_utilities
{

    //
    // Static class.
    //
    filesystem_utilities() = delete;

public:

    //
    // Creates the specified directory recursively.
    //
    static
    status_code
    create_directory(
        const std::string& p_directory_name,
        std::string* p_exception = nullptr);

    //
    // Creates and/or appends data to the specified file.
    //
    static
    status_code
    append_content_to_file(
        const std::string& p_file_path,
        const character* p_content);

    //
    // Gets the size of a file in MiB.
    //
    static
    uint32
    get_file_size(
        const std::string& p_file_path);

};

} // namespace utilities.
} // namespace astra.

#endif