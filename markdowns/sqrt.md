# First AVX Code: SQRT calculation

SQRT Exercise

@[Vectorized SQRT]({"stubs": ["sqrt/sqrt.cpp"], "command": "./mycompile.sh sqrt ./sqrt"})

You will probably see a 650% performance improvement or more.
That is, once you have the data loaded, AVX will perform up to 7 times faster than normal sqrtf. Theorical limit is 800%, but it's rarely achieved. You can expect between 300% and 600% average increase.
>* Note: AVX register load is expensive.