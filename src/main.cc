// *************************************
// Astra Cache Server
// Server
// 'main.cc'
// Author: jcjuarez
// *************************************

#include "astra_cache_server.hh"

int main(int argc, char** argv)
{
    return astra::astra_cache_server::run(std::vector<std::string>(argv, argv + argc));
}