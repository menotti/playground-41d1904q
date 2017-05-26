# SSE & AVX C++ Frameworks

## Intrinsics functions complexity

Working with intrinsic functions directly can be complicated to code and to maintain it. The problem is that intrinsic names are long, and arithmetic operations comes as function notation: `add(a,b)` instead of `a+b`.
The following code is hard to read:
```cpp
x = _mm256_div_ps(_mm256_add_ps(b , _mm256_sqrt_ps(_mm256_sub_ps(_mm256_mul_ps(b , b) , _mm256_mul_ps(_mm256_mul_ps(a , c),_mm256_set1_ps(4.0f))))) , _mm256_mul_ps(a,_mm256_set1_ps(2.0f)));
```
Pretty simple, right?. On the other hand this wrapped version is very readable:
```cpp
x = (b + sqrt( b*b - a*c*4.0f))/(a*2.0f);
```
It's like working with floats, you just need to remember that these variables are vectors. As you may notice, the wrapper allows arithmetic operations of a vector with an scalar (vector * scalar = vector).

## C++ Frameworks for SIMD computation

There are existing frameworks that wraps vector datatypes inside new classes. Then they overload arithmetic, logic and asignment operators to simplify calculations.
Among others, you can use these two frameworks:

1. [Agner Fog's C++ vector class library](http://www.agner.org/optimize/#vectorclass). Complete and updated regularly. Includes trigonometric functions.
2. [Unified Multicore Environment](https://gain-performance.com/ume/). It's a more recent library, I haven't used it personally.

## Reduced size Frameworks

Unfortunately these two frameworks are huge in size, at least for competitive programming where code is limited to hundred of KBs or less.
In cases where you have limitations in code size, you'll need to strip down a shorter version of one of these frameworks.

I have some vector wrappers reduced in size, just focused on one or two types (for example, \_\_m256 8x float and \_\_m128i 8x short, to work with a vector size of 8, both on floats and on integers).

@[Shortened Vector Wrappers]({"stubs": ["framework/framework.cpp","framework/vrandom.h","framework/vconvert.h","framework/v8i.h","framework/v8f.h"], "command": "./mycompile.sh framework ./framework"})

Even being a reduced version, each vector datatype declaration takes up to 150 lines in average (plus some helper functions). Please use this wrappers as a reference for your own version, as it may contains bugs.

Wrapper classes can add overhead to the calls, thus reducing performance. But in my opinion working with intrinsic functions directly is hardly maintainable, cumbersome and prone to errors. 
From now on I'll use wrapper classes to abstract the code from the underlying intrinsics.

In all vector Frameworks you'll find some special functions. These special functions will be widely used on next lessons, if you don't understand it at first glance don't worry, you'll eventually understand the logic behind them.

**Blend-based functions**: Blend is the process to conditionally load vector values based on a mask. This will be explained better on next lessons. In Agner Fog's and my wrapper derived functions are:

1. **`if_select`**`(mask,value_true,value_false)`: Conditional load of a vector based on a mask. If the `mask` is true for a vector component, `value_true` is returned,or `value_false` otherwise. It's a "fake" `if`.
2. **`if_add`**`(mask,value,add_when_true)`: Conditional addition. Returns `value + (mask? add_when_true:0)`, for each vector component.
3. **`if_sub`, `if_mul`, `if_div`**: Similar to `if_add`, just with a different arithmetic operation.

**Horizontal functions**: Horizontal means that these functions operates within a single vector variable, by calculating some logical or arithmetic value.

1. **`horizontal_or`**`(mask)`: If any vector component on the `mask` is true. Returns a boolean.
2. **`horizontal_add`**`(vector)`: Returns the sum of all components of the vector. The returned value is a number (either float, double or int, it depends on the vector type).

>**NOTE:** Agner Fog uses different classes for masks (with `b` suffix) , I just use the same vector classes for the sake of simplicity and code reduction.