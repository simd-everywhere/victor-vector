/* f32x4.h -- Victor Vector Library
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

#if defined(VICTOR_ENABLE_SSE)
  #if !defined(VICTOR_F32X4_H_FORWARD_DECLARE)
    #define VICTOR_F32X4_H_FORWARD_DECLARE

    #if defined(VICTOR_ENABLE_CXX_API)
      namespace Victor {
        class f32x4;
      }
    #endif /* ? defined(__cplusplus)  && !defined(VICTOR_NO_CXX_API)*/
  #elif !defined(VICTOR_F32X4_H_DECLARE)
    #define VICTOR_F32X4_H_DECLARE

    #if defined(VICTOR_ENABLE_CXX_API)
      namespace Victor {
        class f32x4 {
          private:
            __m128 n;

          public:
            inline f32x4(__m128 value);
            inline __m128 to_native(void);
            inline f32x4(float value);
            inline f32x4 operator+(f32x4 a);
            inline f32x4 operator&(f32x4 a);
            inline f32x4 and_not(f32x4 a);
            inline void store(float values[HEDLEY_ARRAY_PARAM(4)]);

            #if defined(VICTOR_ENABLE_SSE2)
              inline i32x4 to_i32x4(void);
            #endif
        };
      }
    #endif /* defined(VICTOR_ENABLE_CXX_API) */

    #if defined(VICTOR_ENABLE_C_API)
      #if defined(VICTOR_ENABLE_VECTOR_EXTENSIONS)
        typedef float victor_f32x4 __attribute__((__vector_size__(16),__aligned__(16)));

        static inline victor_f32x4 victor_f32x4_from_native(__m128 v) {
          union {
            __m128 from;
            victor_f32x4 to;
          } u;
          u.from = v;
          return u.to;
        }

        static inline __m128 victor_f32x4_to_native(victor_f32x4 v) {
          union {
            victor_f32x4 from;
            __m128 to;
          } u;
          u.from = v;
          return u.to;
        }
      #else
        typedef __m128 victor_f32x4;
        #define victor_f32x4_to_native(v) (v)
        #define victor_f32x4_from_native(v) (v)
      #endif
    #endif /* defined(VICTOR_ENABLE_C_API) */

  #elif !defined(VICTOR_F32X4_H_DEFINE)
    #define VICTOR_F32X4_H_DEFINE

    #if defined(VICTOR_ENABLE_CXX_API)
      namespace Victor {
        inline f32x4::f32x4(__m128 value) :n(value) { };
        inline __m128 f32x4::to_native() { return n; }
        inline f32x4::f32x4(float value) :n(_mm_set1_ps(value)) { };
        inline f32x4 f32x4::operator+(f32x4 a) { return f32x4(_mm_add_ps(n, a.to_native())); };
        inline f32x4 f32x4::operator&(f32x4 a) { return f32x4(_mm_and_ps(n, a.to_native())); };
        inline f32x4 f32x4::and_not(f32x4 a) { return f32x4(_mm_andnot_ps(a.to_native(), n)); };
        inline void f32x4::store(float dest[HEDLEY_ARRAY_PARAM(4)]) { _mm_storeu_ps(dest, n); }

        #if defined(VICTOR_ENABLE_SSE2)
          inline i32x4 f32x4::to_i32x4(void) { return i32x4(_mm_castps_si128(n)); };
        #endif
      }
    #endif /* defined(VICTOR_ENABLE_CXX_API) */

    #if defined(VICTOR_ENABLE_C_API)
      static inline victor_f32x4 victor_f32x4_add(victor_f32x4 a, victor_f32x4 b) {
        return victor_f32x4_from_native(_mm_add_ps(victor_f32x4_to_native(a), victor_f32x4_to_native(b)));
      }

      static inline victor_f32x4 victor_f32x4_and(victor_f32x4 a, victor_f32x4 b) {
        return victor_f32x4_from_native(_mm_and_ps(victor_f32x4_to_native(a), victor_f32x4_to_native(b)));
      }

      static inline victor_f32x4 victor_f32x4_and_not(victor_f32x4 a, victor_f32x4 b) {
        return victor_f32x4_from_native(_mm_andnot_ps(victor_f32x4_to_native(b), victor_f32x4_to_native(a)));
      }

      static inline victor_f32x4 victor_f32x4_set1(float value) {
        return victor_f32x4_from_native(_mm_set1_ps(value));
      }

      static inline void victor_f32x4_store(float dest[HEDLEY_ARRAY_PARAM(4)], victor_f32x4 src) {
        _mm_storeu_ps(dest, victor_f32x4_to_native(src));
      }

      #if defined(VICTOR_ENABLE_SSE2)
        static inline victor_i32x4 victor_f32x4_to_i32x4(victor_f32x4 src) {
          return victor_i32x4_from_native(_mm_cvtps_epi32(victor_f32x4_to_native(src)));
        }
      #endif /* defined(VICTOR_ENABLE_SSE2) */
    #endif /* defined(VICTOR_ENABLE_C_API) */
  #endif /* ? defined(VICTOR_F32X4_FORWARD_DECLARE_H) */
#endif /* defined(VICTOR_ENABLE_SSE) */
