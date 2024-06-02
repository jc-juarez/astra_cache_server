// *************************************
// Astra Cache Server
// Utilities
// 'common.hh'
// Author: jcjuarez
// *************************************

#ifndef COMMON_
#define COMMON_

#include <cstdint>
#include "status.hh"

namespace astra
{

//
// Return if failed macro.
//
#define return_if_failed(p_status) if (status::failed(p_status)) { return; }

//
// Return status if failed macro.
//
#define return_status_if_failed(p_status) if (status::failed(p_status)) { return p_status; }

//
// Return status if succeeded macro.
//
#define return_status_if_succeeded(p_status) if (status::succeeded(p_status)) { return p_status; }

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

} // namespace astra.

#endif