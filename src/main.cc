// *************************************
// Astra Caching Server
// Server
// 'main.cc'
// Author: jcjuarez
// *************************************

#include "system_server.hh"

int main(int argc, char** argv)
{
    astra::server::system_server server;
    server.start();
}