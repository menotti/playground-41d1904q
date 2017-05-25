# Masking and Conditional Load

## Masks in Vectors

In the last lesson we presented the mask concept, and it needs a better explanation because it's a critical concept to control the data flow.

A mask is the result of a logical operation between vectors. It has many similarities with booleans (they are the result of logical operations on single numbers, or other booleans), but internally each mask component must have either all 0 bits or all 1 bits.

Let's compare two AVX float vectors with the greater than operator:

![Mask AVX](mask.png)

Inputs are two vectors with float components. The output of the logical operation is also a vector with float components, but its values are all bits set to either 0's or all 1's.
All 1's represents a `TRUE`, and all 0's is a `FALSE`. All 1's are printed as -nan for floats, or -1 on integers. 

**Result of logical operators (>,<,==,&&,etc)**

`vector` `logical op` `vector` = `mask`
`mask` `logical op` `mask` = `mask`
`vector` `logical op` `mask` = `?????` I haven't tested that, I think it will give unexpected results. It's like trying to do `3 > false`, maybe in C++ it works but in a logical way it hasn't any sense.

>**NOTE:** Unlike booleans, not any number different from zero is `TRUE`. Only a vector component with all bits to 1's is considered `TRUE`. Don't use other values as masks, it will fail or will give unexpected results.

## Conditional Load


## Performance 