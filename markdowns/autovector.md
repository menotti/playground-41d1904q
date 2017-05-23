# Automatic Vectorization

## GCC Autovectorization flags

GCC is an advanced compiler, and with the optimization flags `-O3` or `-ftree-vectorize` the compiler will search for loop vectorizations (remember to have the `-mavx` flag too). The source code remains the same, but the compiled code by GCC is completely different.

GCC won't notify anything about automatic vectorization unless some flags are enabled. If you need details of autovectorization results you can use the compiler flags:

- `-fopt-info-vec-optimized` The compiler will notify what loops (by line N°) are being vector optimized.
- `-fopt-info-vec-missed` Detailed info of loops not being vectorized, and a lot of detailed information.
- `-fopt-info-vec-note` Detailed info of all loops and optimizations being done.
- `-fopt-info-vec-all` All previous options together.

>**NOTE:** There are similar `-fopt-info-[options]-optimized` flags for other compiler optimizations, like `inline`: `-fopt-info-inline-optimized`

In this example we will use GCC Autovectorization, enabled with `-O3` and with verbose mode flag `-fopt-info-vec-optimized`. You can change compiler flags to see the different logging options:
@[Autovectorization]({"stubs": ["autovector/autovector.cpp","autovector/compilerflags.txt"], "command": "./mycompileLOG.sh autovector ./autovector"})

If everything is correct, you should see the compiler Test Results:
```
/project/target/autovector/autovector.cpp:22:21: note: loop vectorized
/project/target/autovector/autovector.cpp:15:23: note: loop vectorized
```
With the same code you can test two different things:

- On `compilerflags.txt` file, change log options to `-fopt-info-vec-all` and rerun the Example.
- On `autovector.cpp`, line 1. Change `optimize("O3",` for `optimize("O2",` and rerun.
Non vectorized compilations will be slower than vectorized ones.

## Criterias for loop vectorization

Not all loops can be vectorized, the loop has some strict requeriments.

- The loop count can't change once the loop starts. That means that end of the loop can be a dynamic variable, increasing or decreasing its value at will, but once the loop starts, it must be constant.
- There are limitations to using `break` or `continue` sentences. Sometimes the compiler is clever enough to make it work, but in some cases the loop won't be vectorized. Try to add the  `if (j==27) continue;` as the line 23, right before the `result[j]` asignment, and rerun.
- There are some limits to call external functions inside a loop.
- There shouldn't be data dependencies with other indexes of the loop. I.E. that loop: `for (int i=1; i<N; ++i) x[i]=x[i-1]*2;` Is traversed with a variable i, and data `x[i]` depends on the previous `x[i-1]` value. As AVX registers are loaded in 8 floats, the compiler can't do these calculations on a vector.
- Conditionals sentences (if/else) can be used if it doesn't change the control flow, and are only used to conditionally load A or B values to a C variable. Selecting A or B is created by a mask in the compiler, so it calculates both branches A and B, and the C will store either one value or another:
```csharp
 if ( s >= 0 ) {
 x[i] = (-b[i]+s)/(2.0f*a[i]);
 y[i] = (-b[i]-s)/(2.0f*a[i]);
 }
 else {
 x[i] = 0.0f;
 y[i] = 0.0f;
 }
```
This is a vectorizable loop, the control flow never changes, and x1 and x2 values are just either one or another.

Read [Vectorization with Intel C++ Compilers](https://software.intel.com/sites/default/files/m/4/8/8/2/a/31848-CompilerAutovectorizationGuide.pdf) for additional info on autovectorization. This document is aimed for Intel Compilers, but it gives interesting and complete information about autovectorization.
GCC compiler has one webpage with some information on 
[Auto-vectorization in GCC](https://gcc.gnu.org/projects/tree-ssa/vectorization.html) but it's pretty outdated.

The good thing about autovectorization is that it comes for free. The developer doesn't need to change anything and maybe the loop is vectorized. But sometimes (especially on high performance computing) loops and vectorization need to be fine tuned, ensuring maximum throughput by using manual AVX vectorization. Will see that on the next lessons.