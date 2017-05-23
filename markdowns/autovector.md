# Automatic Vectorization

GCC is an advanced compiler, and with the optimization flags -O3 or -ftree-vectorize the compiler will search for loop vectorizations (remember to have the -mavx flag too). This is done internally, the developer doesn't need to care about how the vectorization is achieved. Nevertheless, the developer need to care about how the data is structured, as we see it later.

GCC won't notify anything about automatic vectorization unless some flags are enabled. If you need details of vectorization results you can use the compiler flags:

- `-fopt-info-vec-optimized` The compiler will notify what loops (by line N°) are being vector optimized.
- `-fopt-info-vec-missed` Detailed info of loops not being vectorized, and a lot of detailed information.
- `-fopt-info-vec-note` Detailed info of all loops and optimizations being done.
- `-fopt-info-vec-all` All previous options together.

>**NOTE:** There are similar `-fopt-info-[options]-optimized` flags for other compiler optimizations, like `inline`: `-fopt-info-inline-optimized`

In this example we will use GCC Autovectorization, enabled with `-ftree-vectorize` and with verbose mode flag `-fopt-info-vec-optimized`. You can change compiler flags to see the different logging options:
@[Autovectorization]({"stubs": ["autovector/autovector.cpp","autovector/compilerflags.txt"], "command": "./mycompileLOG.sh autovector ./autovector"})

If everything is correct, you should see the compiler Test Results:
```
/project/target/autovector/autovector.cpp:23:21: note: loop vectorized
/project/target/autovector/autovector.cpp:16:23: note: loop vectorized
```
With the same code you can test two different things:

- On `compilerflags.txt` file, change log options to `-fopt-info-vec-all` and rerun the Example.
- On `autovector.cpp`, line 1. Change `optimize("O3",` for `optimize("O2",` and rerun.