# First AVX Code: SQRT calculation

Once we reviewed all the requeriments, the autovectorization, and AVX intrinsics, we can create our first manual vectorized program. In this exercise you need to vectorize an sqrt calculation of float numbers. We will use directly the __m256 datatype to store our floats, reducing the overhead in data loading.

@[Vectorized SQRT]({"stubs": ["sqrt/sqrt.cpp"], "command": "./mycompile.sh sqrt ./sqrt"})

You will probably see a 650% performance improvement or more.
That is, once you have the data loaded, AVX will perform up to 7 times faster than normal sqrtf. Theorical limit is 800%, but it's rarely achieved. You can expect between 300% and 600% average increase.