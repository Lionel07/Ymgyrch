#pragma once

#if defined(_M_X64)
#define HOST_64BIT
#endif

#if defined(_M_IX86) || defined(_M_X64)
#define HOST_ENDIAN_LITTLE
#endif