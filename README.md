# Victor Vector Library

## WORK IN PROGRESS

This project is in the **very** early stages.  I'm posting it in hope
of some feedback, and maybe even some help if anyone is interested,
but currently only a handful of functions have been implemented and
it is nowhere near ready for anyone to use.

If you have any thoughts or ideas, please let me know.  You can use the
issue tracker, e-mail, [Twitter](https://twitter.com/nemequ), etc.
Whatever you're comfortable with.

I'm not sure if this project will go anywhere or not.  Right now it's
mostly a PoC, but if there is sufficient interest I'd probably be
willing to continue developing it, so if this is something you'd be
interested in it would probably be a good idea to star the repo if
nothing else.

Also, the name may change.  I just needed a name, and Victor was the
first decent thing that popped into my head (it's a reference to
[Airplane](https://youtu.be/fVq4_HhBK8Y)).  Other things that may
change include, but are not limited to:

 * The C namespace (`victor_*`) may end up being `vic_*` or something
   else, even if the name doesn't change.

## Introduction

The Victor Vector Library is intended to be an alternative to the
official x86 SIMD APIs.  Basically, I've never liked Intel's API,
and Victor is what I wish the Intel APIs looked like.

The major differences compared to the official APIs:

 * Doesn't require aliasing in your code.
 * Types are consistent and sane (I'm looking at you,
   [_mm_loadu_si128](https://software.intel.com/sites/landingpage/IntrinsicsGuide/#text=loadu_si&expand=3416)).
 * Uses standard fixed-size types (int8_t, int16_t, uint16_t, etc.
   instead of char, short, unsigned short, etc.).
 * There are C and C++ APIs.

Victor should offer exactly the same performance as the Intel APIs,
just with a better (IMHO) API.

## Why Bother?

For one thing, it's much safer.  Using different types instead of
shoving everything into `__m128i`/`__m256i`/`__m512i` means the
compiler can catch a lot of bugs that the Intel APIs can't.

The C++ API be more comfortable for people using C++, though of course
you can still use the C API in C++ if you prefer it.

Victor also isn't stuck with some poor legacy decisions.  For example,
[`_mm_loadu_si128`](https://software.intel.com/sites/landingpage/IntrinsicsGuide/#text=_loadu_si&expand=3416)
(and many other functions) have parameters which are pointers to
`__m128i`, which means they should be aligned to `alignof(__m128i)`
(i.e., 16-byte) boundaries.  However, the function is used specifically
for unaligned data; for aligned data, there is `_mm_load_si128`.

## What does it look like?

It's really pretty straightforward.  Most functions follow a similar
naming convention to the Intel APIs so if you already know Intel's
APIs the change should be pretty easy.  For example, the Victor
equivalent of `_mm_set1_ps` in C is `victor_f32x4_set1`.

Functions for loading are mostly implemented as constructors.

For example, consider a few  functions using the Intel APIs:

```c
__m128i foo(__m128i a, __m128i b) {
  return _mm_add_epi32(a, m);
}

__m128i bar(int value) {
  return _mm_set1_epi32(value);
}

__m128i baz(int* value) {
  return _mm_loadu_epi32((__m128i*) value);
}
```

### C++

In C++ it would look like:

```c++
Victor::i32x4 foo(Victor::i32x4 a, Victor::i32x4 b) {
  return a + b;
}

Victor::i32x4 bar(int32_t value) {
  return Victor::i32x4(value);
}

Victor::i32x4 baz(int32_t values[]) {
  return Victor::i32x4(values);
}
```

Obviously, you can use `using namespace Victor;` to get rid of all the
`Victor::` noise:

```c++
using namespace Victor;

i32x4 foo(i32x4 a, i32x4 b) {
  return a + b;
}

i32x4 bar(int32_t value) {
  return i32x4(value);
}

i32x4 baz(int32_t values[]) {
  return i32x4(values);
}
```

### C

In C, it would look like:

```c
victor_i32x4 foo(victor_i32x4 a, victor_i32x4 b) {
  return victor_i32x4_add(a, b);
}

victor_i32x4 bar(int32_t value) {
  return victor_i32x4_set1(value);
}

victor_i32x4 baz(int32_t values[4]) {
  return victor_i32x4_load(values);
}
```

### Interacting with Intel's APIs

Converting to/from Victor's types to the equivalent Intel types is
easy, so you can mix the two without much effort.  Hopefully this
makes porting or interacting with legacy code easy.

In C++, all Victor classes have `to_native()` methods which return the
underlying native type (for example, `float32x4::to_native()` returns
an `__m128`).  To go the other way just pass the native value to the
constructor (*e.g.*, `float32x4((__m128) foo)`).

In C, you just use `victor_*_to_native()` to convert to the Intel types
and `victor_*_from_native()` to convert from them.

If you need to convert between Victor's C and C++ APIs, you can use the
constructor to convert to C++ and `victor_*_to_c()` to convert to C.

## Portability

Victor is implemented using the Intel APIs, so it is inherently limited
to the same systems for which the Intel APIs are available.

That said, [SIMDe](https://github.com/nemequ/simde) (another one of my
projects) offers portable implementations of the Intel APIs and can be
used in conjuction with Victor.  Just define
`SIMDE_ENABLE_NATIVE_ALIASES` and include the relevant header (*e.g.*,
`simde/x86/avx.h`) before including Victor and it should work pretty
much anywhere.

## Does Victor support dynamic dispatch or length-agnostic vectors?

Not natively.  It is intended to operate at a similar level to the
Intel APIs.  You could add a layer on top of Victor to do this type
of stuff, just like you can for Intel's APIs.
