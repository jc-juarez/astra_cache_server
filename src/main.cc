// *************************************
// Astra Cache Server
// Server
// 'main.cc'
// Author: jcjuarez
// *************************************

#include "common.hh"
#include "logger.hh"
#include "system_server.hh"
#include "system_configuration.hh"

int main(int argc, char** argv)
{
    using namespace astra;

    status_code status = status::success;

    std::vector<std::string> command_line_arguments(argv, argv + argc);

    //
    // Initialize the system configuration for all components.
    //
    system_configuration astra_system_configuration(
        &status,
        command_line_arguments);

    if (status::failed(status))
    {
        logger::log_error_fallback(std::format("<!> Astra cache server initial system configuration failed. Status={:#X}.\n",
            status).c_str());

        return EXIT_FAILURE;
    }

    //
    // Initialize singleton logger for the system.
    //
    status = logger::initialize(astra_system_configuration.m_logger_configuration);

    if (status::failed(status))
    {
        logger::log_error_fallback(std::format("<!> Astra cache server initial system configuration failed. Status={:#X}.\n",
            status).c_str());

        return EXIT_FAILURE;
    }


    astra::server::system_server server;
    server.start();
}