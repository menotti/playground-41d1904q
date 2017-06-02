# First AVX Code: SQRT calculation

Now that we have reviewed all the requirements, the autovectorization, and AVX intrinsics, we can create our first manually vectorized program. In this exercise, you need to vectorize a sqrt calculation of float numbers. We will explicitly use the \_\_m256 datatype to store our floats, reducing the overhead in data loading.

@[Vectorized SQRT]({"stubs": ["sqrt/sqrt.cpp"], "command": "./mycompile.sh sqrt ./sqrt"})

You will probably see a 600% performance improvement or more.
That is, once you have the data loaded, AVX will perform up to 7 times faster than normal sqrtf. The theoretical limit is 800%, but it's rarely achieved. You can expect between a 300% and 600% average increase.
