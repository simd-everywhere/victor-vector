# Mapping Intel Functions to/from Victor Vector Library

Note that there is not always a 1:1 mapping.  Sometimes there are
multiple Victor functions which map to a single Intel function.

## SSE

| ISAX | Function | Victor C++ | Victor C |
| `_mm_add_ps(float a)` | `i32x4::operator+(float b)` | `victor_i32x4_add(victor_i32x4 a, victor_i32x4 b)` |
| `_mm_and_ps(float a)` | `i32x4::operator&(float b)` | `victor_i32x4_and(victor_i32x4 a, victor_i32x4 b)` |
| `_mm_set1_ps(float a)` | `f32x4::f32x4(float a)` | `victor_f32x4_set1(float a)` |
| `_mm_storeu_ps(void* mem_addr, __m128 a)` | `f32x4::store(int32_t dest[])` | `victor_f32x4_store(int32_t dest[4], victor_f32x4 src)` |

## SSE2

| ISAX | Function | Victor C++ | Victor C |
| `_mm_add_epi32(__m128i a)` | `i32x4::operator+(i32x4 b)` | `victor_i32x4_add(victor_i32x4 a, victor_i32x4 b)` |
| `_mm_and_epi32(__m128i a)` | `i32x4::operator&(i32x4 b)` | `victor_i32x4_and(victor_i32x4 a, victor_i32x4 b)` |
| `_mm_castps_si128(__m128 a)` | `f32x4::to_i32x4()` | `victor_f32x4_to_i32x4(victor_f32x4 src)` |
| `_mm_castsi128_epi32(__m128i a)` | `i32x4::to_f32x4()` | `victor_i32x4_to_f32x4(victor_i32x4 src)` |
| `_mm_set1_epi32(int32_t a)` | `i32x4::i32x4(int32_t a)` | `victor_i32x4_set1(int32_t a)` |
| `_mm_storeu_epi32(void* mem_addr, __m128i a)` | `i32x4::store(int32_t dest[])` | `victor_i32x4_store(int32_t dest[4], victor_i32x4 src)` |
