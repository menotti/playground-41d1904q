# SSE & AVX C++ Frameworks

## Intrinsics functions complexity

Working with intrinsic functions directly can be complicated to code, and to maintain it. The problem is that intrinsic names are long, and arithmetic operations comes as function notation: `add(a,b)` instead of `a+b`.
The following code is hard to read:
```cpp
x = _mm256_div_ps(_mm256_add_ps(b , _mm256_sqrt_ps(_mm256_sub_ps(_mm256_mul_ps(b , b) , _mm256_mul_ps(_mm256_mul_ps(a , c),_mm256_set1_ps(4.0f))))) , _mm256_mul_ps(a,_mm256_set1_ps(2.0f)));
```
Pretty simple, right?. On the other hand this wrapped version is very readable:
```cpp
x = (b + sqrt( b*b - a*c*4.0f))/(a*2.0f);
```
It's like working with floats, you just need to remember that these variables are vectors.

## C++ Frameworks for SIMD computation

There are existing frameworks that wraps vector datatypes inside new classes. Then they overload arithmetic, logic and asignment operators to simplify the calculations.
Among others, you can use these two frameworks:

1. [Agner Fog's C++ vector class library](http://www.agner.org/optimize/#vectorclass). Complete and updated regularly. Includes trigonometric functions.
2. [Unified Multicore Environment](https://gain-performance.com/ume/). It's a more recent library, I haven't used it personally, the source code is at [https://github.com/edanor/umesimd](https://github.com/edanor/umesimd).

## Reduced size Frameworks

Unfortunately these two frameworks are huge in size, at least for competitive programming where code is limited to hundred of KBs or less.
In cases where you have limitations in code size, you'll need to strip down a shorter version of one of these frameworks.

I have some vector wrappers reduced in size, just focused on one or two types (for example, \_\_m256 8x float and \_\_m128i 8x short, to work with a vector size of 8, both on floats and on integers).

@[Reduced Vector Wrappers]({"stubs": ["framework/framework.cpp","framework/helpers.h","framework/v8i.h","framework/v8f.h"], "command": "./mycompile.sh framework ./framework"})

Wrapper classes can add overhead to the calls, thus reducing performance. But in my opinion working with intrinsic functions directly is hardly maintainable, cumbersome and prone to errors. 
From now on I'll use wrapper classes to abstract the code from the underlying intrinsics.