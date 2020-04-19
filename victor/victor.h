/* Victor Vector Library
 * Copyright (c) 2020 Evan Nemerson <evan@nemerson.com> 
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "hedley.h"
#include <stdint.h>

#if !defined(VICTOR_COMMON_H)
#define VICTOR_COMMON_H
#define VICTOR_INSIDE_COMMON_H

/* Figure out which ISA extensions are available.  Usually the compiler
   will tell us, but you can define VICTOR_ENABLE_* prior to including
   this header to force support for an ISAX, or you can include the
   relevant header from SIMDe <https://github.com/nemequ/simde> (after
   defining SIMDE_ENABLE_NATIVE_ALIASES). */

#if !defined(VICTOR_ENABLE_AVX2)
  #if defined(SIMDE__AVX2_H) || defined(__AVX2__)
    #define VICTOR_ENABLE_AVX2
  #endif
#endif
#if defined(VICTOR_ENABLE_AVX2)
  #define VICTOR_ENABLE_AVX
#endif

#if !defined(VICTOR_ENABLE_AVX)
  #if defined(SIMDE__AVX_H) || defined(__AVX__)
    #define VICTOR_ENABLE_AVX
  #endif
#endif
#if defined(VICTOR_ENABLE_AVX)
  #if !defined(SIMDE__AVX_H)
    #include <immintrin.h>
  #endif
  #define VICTOR_ENABLE_SSE4_2
#endif

#if !defined(VICTOR_ENABLE_SSE4_2)
  #if defined(SIMDE__SSE4_2_H) || defined(__SSE4_2__)
    #define VICTOR_ENABLE_SSE4_2
  #endif
#endif
#if defined(VICTOR_ENABLE_SSE4_2)
  #if !defined(SIMDE__SSE4_2_H)
    #include <nmmintrin.h>
  #endif
  #define VICTOR_ENABLE_SSE4_1
#endif

#if !defined(VICTOR_ENABLE_SSE4_1)
  #if defined(SIMDE__SSE4_1_H) || defined(__SSE4_1__)
    #define VICTOR_ENABLE_SSE4_1
  #endif
#endif
#if defined(VICTOR_ENABLE_SSE4_1)
  #if !defined(SIMDE__SSE4_1_H)
    #include <smmintrin.h>
  #endif
  #define VICTOR_ENABLE_SSSE3
#endif

#if !defined(VICTOR_ENABLE_SSSE3)
  #if defined(SIMDE__SSSE3_H) || defined(__SSSE3__)
    #define VICTOR_ENABLE_SSSE3
  #endif
#endif
#if defined(VICTOR_ENABLE_SSSE3)
  #if !defined(SIMDE__SSSE3_H)
    #include <tmmintrin.h>
  #endif
  #define VICTOR_ENABLE_SSE3
#endif

#if !defined(VICTOR_ENABLE_SSE3)
  #if defined(SIMDE__SSE3_H) || defined(__SSE3__)
    #define VICTOR_ENABLE_SSE3
  #endif
#endif
#if defined(VICTOR_ENABLE_SSE3)
  #if !defined(SIMDE__SSE3_H)
    #include <pmmintrin.h>
  #endif
  #define VICTOR_ENABLE_SSE2
#endif

#if !defined(VICTOR_ENABLE_SSE2)
  #if defined(SIMDE__SSE2_H) || defined(__SSE2__)
    #define VICTOR_ENABLE_SSE2
  #elif defined(_M_IX86_FP)
    #if _M_IX86_FP >= 2
      #define VICTOR_ENABLE_SSE2
    #endif
  #endif
#endif
#if defined(VICTOR_ENABLE_SSE2)
  #if !defined(SIMDE__SSE2_H)
    #include <emmintrin.h>
  #endif
  #define VICTOR_ENABLE_SSE
#endif

#if !defined(VICTOR_ENABLE_SSE)
  #if defined(SIMDE__SSE_H) || defined(__SSE__)
    #define VICTOR_ENABLE_SSE
  #elif defined(_M_IX86_FP)
    #if _M_IX86_FP >= 1
      #define VICTOR_ENABLE_SSE
    #endif
  #endif
#endif
#if defined(VICTOR_ENABLE_SSE)
  #if !defined(SIMDE__SSE_H)
    #include <xmmintrin.h>
  #endif
  #define VICTOR_ENABLE_SSE
#endif

/* If we have GCC-style vector extensions available we'll use them
   instead of using __m(128|256|512)(i|d)? directly.  This gives us
   warnings if we try to assign from types we would like to be
   incompatible but aren't in Intel's APIs.  For example, assigning
   an int32x4 to an int16x8 variable.
   
   If you're using MSVC, sorry, you don't get this feature.  Most
   other compilers in widespread use support it, though. */
#if !defined(VICTOR_ENABLE_VECTOR_EXTENSIONS)
  #if \
      HEDLEY_HAS_ATTRIBUTE(vector_size) || \
      HEDLEY_GCC_VERSION_CHECK(4,8,0) || \
      HEDLEY_INTEL_VERSION_CHECK(16,0,0) || \
      HEDLEY_SUNPRO_VERSION_CHECK(5,2,0) || \
      HEDLEY_PGI_VERSION_CHECK(18,4,0)
    #define VICTOR_ENABLE_VECTOR_EXTENSIONS
  #endif
#endif

/* By default, we the C API in C, and both the C and C++ APIs in C++.
   If you want to skip defining one you can define VICTOR_NO_C_API
   or VICTOR_NO_CXX_API */
#if !defined(VICTOR_NO_C_API)
  #define VICTOR_ENABLE_C_API
#endif
#if !defined(VICTOR_NO_CXX_API) && defined(__cplusplus)
  #define VICTOR_ENABLE_CXX_API
#endif

/* Victor uses three passes for including headers:
 *
 * 1. Forward declarations so we can use any type in declarations.  For
 *    example, float32x4 needs to use int32x4 for to_int32x4, and
 *    int32x4 needs float32x4 for to_float32x4.
 * 2. Declarations.
 * 3. Definitions.
 */

/* Forward declarations */
#include "i8x16.h"
#include "i32x4.h"
#include "f32x4.h"

/* Declarations */
#include "i8x16.h"
#include "i32x4.h"
#include "f32x4.h"

/* Definitions */
#include "i8x16.h"
#include "i32x4.h"
#include "f32x4.h"

#undef VICTOR_INSIDE_COMMON_H

#endif /* !defined(VICTOR_COMMON_H) */