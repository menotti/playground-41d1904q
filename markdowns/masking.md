# Masking and Conditional Load

## Masks in Vectors

In the previous lesson we presented the mask concept. As it's a critical concept to control the data flow, it needs a better explanation.

A mask is the result of a logical operation between vectors. It has many similarities with booleans (they are the result of logical operations on single numbers, or other booleans), but internally each mask component must have either all 0 bits or all 1 bits.

Let's compare two AVX float vectors with the greater-than operator:

![Mask AVX](mask.png)

The inputs are two vectors with float components. The output of the logical operation is also a vector with float components, but its values have the bits set to either all 0's or all 1's.
All 1's represents a `TRUE`, and all 0's is a `FALSE`. The all 1's value is printed as `-nan` for floats, or -1 for integers. The real value stored isn't important. We just need to know that it holds true and false values.

**Result of logical operators (>,<,==,&&,||,etc)**

Using the logical && operator as an example:

- `vector && vector` = `mask`
- `mask && mask` = `mask`
- `vector && mask` = `?????` 

I haven't tested the last case, I think it will give unexpected results. It's like trying to do `3 > false`, maybe in C++ this works, but in a logical sense it's incorrect.

>**NOTE:** Unlike booleans, not just any number other than zero is `TRUE`. Only a vector component with all bits set to 1 is considered `TRUE`. Don't use other values as masks. It will fail or it will give unexpected results.

## Conditional Load

Masks can be used to conditionally load values into vectors.
In you recall the blend-based functions. All of them used masks to conditionally control the load of values into vectors:
**`if_select`**`(mask,value_true,value_false)` can be represented as:

![if_select](ifselect.png)

When the mask is set to `FALSE`, data is loaded from `value_false` vector, and when `TRUE`, it comes from `value_true`.
The concept is simple but effective.

In the next exercise, you must load a vector according the following conditions:
```cpp
if (value > 3.0f || (value <=-3.7f && value > -15.0f)) {
   return sqrt(2.0f*value+1.5f);
 }
 else {
   return (-2.0f*value-8.7f);
 }
```
@[Masked load]({"stubs": ["masked/masked.cpp","masked/v8f.h"], "command": "./mycompile.sh masked ./masked"})


>**NOTE:** **`if_select`** IS NOT an intrinsic function name. It's my wrapper for **`_mm256_blendv_ps`**. Please note that `_mm256_blendv_ps` has a very, very different parameter ordering! blendv has the mask as the last parameter!

## Performance 

Conditional loads using masks aren't real branches so they don't have mispredictions, and the CPU can make better use of out-of-order execution.
But this comes with a price. Since they're branchless, and all the conditional execution is done with mask operations, both branches are always calculated and executed.
If you have a pretty complex calculation for value_false, it will always be calculated, even if it happens only 0.00001% of the time.
This can lead to performance problems if there are parts of the code that are rarely needed, but computationally very expensive.

In the next lesson, we will learn some ways to control the data flow, being able to exit loops early based on some conditions.

