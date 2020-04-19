/* i8x16.h -- Victor Vector Library
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
  #if !defined(VICTOR_I8X16_H_FORWARD_DECLARE)
    #define VICTOR_I8X16_H_FORWARD_DECLARE

    #if defined(VICTOR_ENABLE_CXX_API)
      namespace Victor {
        class i8x16;
      }
    #endif /* ? defined(__cplusplus)  && !defined(VICTOR_NO_CXX_API)*/
  #elif !defined(VICTOR_I8X16_H_DECLARE)
    #define VICTOR_I8X16_H_DECLARE

    #if defined(VICTOR_ENABLE_CXX_API)
      namespace Victor {
        class i8x16 {
          private:
            __m128i n;

          public:
            inline i8x16(__m128i value);
            inline __m128i to_native(void);
            inline i8x16(int8_t value);
            inline i8x16(int8_t e0, int8_t e1, int8_t  e2, int8_t  e3, int8_t  e4, int8_t  e5, int8_t  e6, int8_t  e7,
                         int8_t e8, int8_t e9, int8_t e10, int8_t e11, int8_t e12, int8_t e13, int8_t e14, int8_t e15);
            inline i8x16 operator+(i8x16 a);
            inline i8x16 operator&(i8x16 a);
            inline i8x16 and_not(i8x16 a);
            inline void store(int8_t values[HEDLEY_ARRAY_PARAM(4)]);

            inline f32x4 as_f32x4(void);
        };
      }
    #endif /* defined(VICTOR_ENABLE_CXX_API) */

    #if defined(VICTOR_ENABLE_C_API)
      #if defined(VICTOR_ENABLE_VECTOR_EXTENSIONS)
        typedef int8_t victor_i8x16 __attribute__((__vector_size__(16),__aligned__(16)));

        static inline victor_i8x16 victor_i8x16_from_native(__m128i v) {
          union {
            __m128i from;
            victor_i8x16 to;
          } u;
          u.from = v;
          return u.to;
        }

        static inline __m128i victor_i8x16_to_native(victor_i8x16 v) {
          union {
            victor_i8x16 from;
            __m128i to;
          } u;
          u.from = v;
          return u.to;
        }
      #else
        typedef __m128i victor_i8x16;
        #define victor_i8x16_to_native(v) (v)
        #define victor_i8x16_from_native(v) (v)
      #endif
    #endif /* defined(VICTOR_ENABLE_C_API) */

  #elif !defined(VICTOR_I8X16_H_DEFINE)
    #define VICTOR_I8X16_H_DEFINE

    #if defined(VICTOR_ENABLE_CXX_API)
      namespace Victor {
        inline i8x16::i8x16(__m128i value) :n(value) { };
        inline __m128i i8x16::to_native() { return n; }
        inline i8x16::i8x16(int8_t value) :n(_mm_set1_epi8(value)) { };
        inline i8x16::i8x16(int8_t e0, int8_t e1, int8_t  e2, int8_t  e3, int8_t  e4, int8_t  e5, int8_t  e6, int8_t  e7,
                            int8_t e8, int8_t e9, int8_t e10, int8_t e11, int8_t e12, int8_t e13, int8_t e14, int8_t e15)
          :n(_mm_setr_epi8(e0, e1,  e2,  e3,  e4,  e5,  e6,  e7,
                           e8, e9, e10, e11, e12, e13, e14, e15)) { };
        inline i8x16 i8x16::operator+(i8x16 a) { return i8x16(_mm_add_epi8(n, a.to_native())); };
        inline i8x16 i8x16::operator&(i8x16 a) { return i8x16(_mm_and_si128(n, a.to_native())); };
        inline i8x16 i8x16::and_not(i8x16 a) { return i8x16(_mm_andnot_si128(n, a.to_native())); };
        inline void i8x16::store(int8_t dest[HEDLEY_ARRAY_PARAM(4)]) { _mm_storeu_si128(HEDLEY_REINTERPRET_CAST(__m128i*, dest), n); }

        inline f32x4 i8x16::as_f32x4(void) { return f32x4(_mm_castsi128_ps(n)); };
      }
    #endif /* defined(VICTOR_ENABLE_CXX_API) */

    #if defined(VICTOR_ENABLE_C_API)
      static inline victor_i8x16 victor_i8x16_add(victor_i8x16 a, victor_i8x16 b) {
        return victor_i8x16_from_native(_mm_add_epi8(victor_i8x16_to_native(a), victor_i8x16_to_native(b)));
      }

      static inline victor_i8x16 victor_i8x16_and(victor_i8x16 a, victor_i8x16 b) {
        return victor_i8x16_from_native(_mm_and_si128(victor_i8x16_to_native(a), victor_i8x16_to_native(b)));
      }

      static inline victor_i8x16 victor_i8x16_andnot(victor_i8x16 a, victor_i8x16 b) {
        return victor_i8x16_from_native(_mm_andnot_si128(victor_i8x16_to_native(b), victor_i8x16_to_native(a)));
      }

      static inline victor_i8x16 victor_i8x16_set1(int8_t value) {
        return victor_i8x16_from_native(_mm_set1_epi8(value));
      }

      static inline victor_i8x16 victor_i8x16_set(int8_t e0, int8_t e1, int8_t  e2, int8_t  e3, int8_t  e4, int8_t  e5, int8_t  e6, int8_t  e7,
                                                  int8_t e8, int8_t e9, int8_t e10, int8_t e11, int8_t e12, int8_t e13, int8_t e14, int8_t e15) {
        return victor_i8x16_from_native(_mm_setr_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15));
      }

      static inline void victor_i8x16_store(int8_t dest[HEDLEY_ARRAY_PARAM(4)], victor_i8x16 src) {
        _mm_storeu_si128(HEDLEY_REINTERPRET_CAST(__m128i*, dest), victor_i8x16_to_native(src));
      }

      static inline victor_f32x4 victor_i8x16_as_f32x4(victor_i8x16 src) {
        return victor_f32x4_from_native(_mm_castsi128_ps(victor_i8x16_to_native(src)));
      }
    #endif /* defined(VICTOR_ENABLE_C_API) */
  #endif /* ? defined(VICTOR_I8X16_FORWARD_DECLARE_H) */
#endif /* defined(VICTOR_ENABLE_SSE2) */
