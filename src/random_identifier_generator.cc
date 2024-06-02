// *************************************
// Astra Cache Server
// Utilities
// 'random_identifier_generator.cc'
// Author: jcjuarez
// *************************************

#include <format>
#include "random_identifier_generator.hh"

namespace astra
{

random_identifier_generator::random_identifier_generator()
{
    try
    {
        m_random_number_generator.seed(std::random_device{}());
    }
    catch (const std::exception& exception)
    {
        m_random_number_generator.seed(static_cast<uint32>(std::time(nullptr)));
    }
}

std::string
random_identifier_generator::generate_double_random_identifier()
{
    return std::format(
        "{}-{}",
        generate_random_number(),
        generate_random_number());
}

std::string
random_identifier_generator::generate_triple_random_identifier()
{
    return std::format(
        "{}-{}-{}",
        generate_random_number(),
        generate_random_number(),
        generate_random_number());
}

uint64
random_identifier_generator::generate_random_number()
{
    std::scoped_lock<std::mutex> lock(m_lock);
    
    return m_random_number_distribution(m_random_number_generator);
}

} // namespace astra.