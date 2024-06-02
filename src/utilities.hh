// *************************************
// Astra Caching Server
// Utilities
// 'utilities.hh'
// Author: jcjuarez
// *************************************

#ifndef UTILITIES_
#define UTILITIES_

#include <cstdint>

namespace astra
{

//
// Unsigned 1 byte.
//
using byte = std::uint8_t;
using uint8 = std::uint8_t;

//
// Unsigned 2 bytes.
//
using uint16 = std::uint16_t;

//
// Unsigned 4 bytes.
//
using uint32 = std::uint32_t;

//
// Unsigned 8 bytes.
//
using uint64 = std::uint64_t;

//
// Signed 1 byte.
//
using int8 = std::int8_t;
using character = char;

//
// Signed 2 bytes.
//
using int16 = std::int16_t;

//
// Signed 4 bytes.
//
using int32 = std::int32_t;

//
// Signed 8 bytes.
//
using int64 = std::int64_t;

//
// Single-precision 4 bytes floating point.
//
using single_precision = float;

//
// Double-precision 8 bytes floating point.
//
using double_precision = double;

} // namespace modula.

#endif