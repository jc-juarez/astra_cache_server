// *************************************
// Astra Cache Server
// Utilities
// 'filesystem_utilities.cc'
// Author: jcjuarez
// *************************************

#include <fstream>
#include <filesystem>
#include "filesystem_utilities.hh"

namespace astra
{
namespace utilities
{

status_code
filesystem_utilities::create_directory(
    const std::string& p_directory_name,
    std::string* p_exception)
{
    try
    {
        std::filesystem::create_directories(p_directory_name);
    }
    catch (const std::filesystem::filesystem_error& exception)
    {
        if (p_exception != nullptr)
        {
            *p_exception = exception.what();
        }

        return status::directory_creation_failed;
    }

    return status::success;
}

status_code
filesystem_utilities::append_content_to_file(
    const std::string& p_file_path,
    const character* p_content)
{
    std::ofstream file;

    file.open(p_file_path, std::ios_base::app);

    if (!file)
    {
        return status::file_write_failed;
    }

    file << p_content;

    return status::success;
}

uint32
filesystem_utilities::get_file_size(
    const std::string& p_file_path)
{
    uint32 file_size_mib = 0;

    try
    {
        uint32 file_size_bytes = static_cast<uint32>(std::filesystem::file_size(p_file_path));
        file_size_mib = file_size_bytes / (1024u * 1024u);
    }
    catch (const std::filesystem::filesystem_error& exception)
    {
        //
        // Consider a failed retrieval as size of 0 MiB.
        //
    }

    return file_size_mib;
}

} // namespace utilities.
} // namespace astra.