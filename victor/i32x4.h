/* i32x4.h -- Victor Vector Library
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

#if !defined(VICTOR_COMMON_H)
  #include "victor.h"
#endif /* !defined(VICTOR_COMMON_H) */

#if defined(VICTOR_ENABLE_SSE2)
  #if !defined(VICTOR_I32X4_H_FORWARD_DECLARE)
    #define VICTOR_I32X4_H_FORWARD_DECLARE

    #if defined(VICTOR_ENABLE_CXX_API)
      namespace Victor {
        class i32x4;
      }
    #endif /* ? defined(__cplusplus)  && !defined(VICTOR_NO_CXX_API)*/
  #elif !defined(VICTOR_I32X4_H_DECLARE)
    #define VICTOR_I32X4_H_DECLARE

    #if defined(VICTOR_ENABLE_CXX_API)
      namespace Victor {
        class i32x4 {
          private:
            __m128i n;

          public:
            inline i32x4(__m128i value);
            inline __m128i to_native(void);
            inline i32x4(int32_t value);
            inline i32x4 operator+(i32x4 a);
            inline i32x4 operator&(i32x4 a);
            inline i32x4 and_not(i32x4 a);
            inline void store(int32_t values[HEDLEY_ARRAY_PARAM(4)]);

            inline f32x4 to_f32x4(void);
        };
      }
    #endif /* defined(VICTOR_ENABLE_CXX_API) */

    #if defined(VICTOR_ENABLE_C_API)
      #if defined(VICTOR_ENABLE_VECTOR_EXTENSIONS)
        typedef int32_t victor_i32x4 __attribute__((__vector_size__(16),__aligned__(16)));

        static inline victor_i32x4 victor_i32x4_from_native(__m128i v) {
          union {
            __m128i from;
            victor_i32x4 to;
          } u;
          u.from = v;
          return u.to;
        }

        static inline __m128i victor_i32x4_to_native(victor_i32x4 v) {
          union {
            victor_i32x4 from;
            __m128i to;
          } u;
          u.from = v;
          return u.to;
        }
      #else
        typedef __m128i victor_i32x4;
        #define victor_i32x4_to_native(v) (v)
        #define victor_i32x4_from_native(v) (v)
      #endif
    #endif /* defined(VICTOR_ENABLE_C_API) */

  #elif !defined(VICTOR_I32X4_H_DEFINE)
    #define VICTOR_I32X4_H_DEFINE

    #if defined(VICTOR_ENABLE_CXX_API)
      namespace Victor {
        inline i32x4::i32x4(__m128i value) :n(value) { };
        inline __m128i i32x4::to_native() { return n; }
        inline i32x4::i32x4(int32_t value) :n(_mm_set1_epi32(value)) { };
        inline i32x4 i32x4::operator+(i32x4 a) { return i32x4(_mm_add_epi32(n, a.to_native())); };
        inline i32x4 i32x4::operator&(i32x4 a) { return i32x4(_mm_and_si128(n, a.to_native())); };
        inline i32x4 i32x4::and_not(i32x4 a) { return i32x4(_mm_andnot_si128(n, a.to_native())); };
        inline void i32x4::store(int32_t dest[HEDLEY_ARRAY_PARAM(4)]) { _mm_storeu_si128(HEDLEY_REINTERPRET_CAST(__m128i*, dest), n); }

        inline f32x4 i32x4::to_f32x4(void) { return f32x4(_mm_castsi128_ps(n)); };
      }
    #endif /* defined(VICTOR_ENABLE_CXX_API) */

    #if defined(VICTOR_ENABLE_C_API)
      static inline victor_i32x4 victor_i32x4_add(victor_i32x4 a, victor_i32x4 b) {
        return victor_i32x4_from_native(_mm_add_epi32(victor_i32x4_to_native(a), victor_i32x4_to_native(b)));
      }

      static inline victor_i32x4 victor_i32x4_and(victor_i32x4 a, victor_i32x4 b) {
        return victor_i32x4_from_native(_mm_and_si128(victor_i32x4_to_native(a), victor_i32x4_to_native(b)));
      }

      static inline victor_i32x4 victor_i32x4_andnot(victor_i32x4 a, victor_i32x4 b) {
        return victor_i32x4_from_native(_mm_andnot_si128(victor_i32x4_to_native(b), victor_i32x4_to_native(a)));
      }

      static inline victor_i32x4 victor_i32x4_set1(int32_t value) {
        return victor_i32x4_from_native(_mm_set1_epi32(value));
      }

      static inline void victor_i32x4_store(int32_t dest[HEDLEY_ARRAY_PARAM(4)], victor_i32x4 src) {
        _mm_storeu_si128(HEDLEY_REINTERPRET_CAST(__m128i*, dest), victor_i32x4_to_native(src));
      }

      static inline victor_f32x4 victor_i32x4_to_f32x4(victor_i32x4 src) {
        return victor_f32x4_from_native(_mm_cvtepi32_ps(victor_i32x4_to_native(src)));
      }
    #endif /* defined(VICTOR_ENABLE_C_API) */
  #endif /* ? defined(VICTOR_I32X4_FORWARD_DECLARE_H) */
#endif /* defined(VICTOR_ENABLE_SSE2) */
