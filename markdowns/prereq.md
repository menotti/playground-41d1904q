# Prerequisites

SSE/AVX has prerequisites on the architecture of the target machine. In this Course, the binary builds will only target the current machine. That is, we'll use the `arch=native` GCC flag to detect CPU capabilities and use them accordingly.

>**Note:** Compiled binaries will fail on machines without AVX capabilities. If you need a binary that adapts to different CPUs, you'll need to either make use of CPU identification and call different functions, or make different binaries targeted at different instruction sets.

As stated on the introduction, the OS, the compiler, and the CPU must all allow AVX extensions.
We can run this script to detect system capabilities:

@[Detect System Capabilities]({"stubs": ["prereq/detect.sh"], "command": "./run.sh ./prereq/detect.sh"})

In the `CPU flag capabilities`, we'll search for the `avx` flag. This identifies the CPU as AVX compatible. If you have `avx2` that means the CPU allows AVX2 extensions. AVX is enough to have 8x32bit float vectors. AVX2 adds 256bits vectors for integers (8x32bit integers for example). Nevertheless, 256bit integer vectors seem to be executed the same as two 128bit vectors, so performance is not greatly improved from SSE 128bit integer vectors.

In the `GCC capabilities` we'll search for the **`#define __AVX__ 1`** pragma. This indicates that the AVX branches will be enabled.
>**Alway use -march=native or -mavx !!** If you run GCC without the correct march you **won't** get the \_\_AVX\_\_ flag!!! Default GCC parameters are generic, and without the flag it won't enable AVX even if the CPU is AVX capable.

Finally, we recheck that Linux Kernel is `2.6.30` or greater. A kernel `4.4.0` or greater is ideal.

With all these prerequisites, we are ready to code our first AVX vectorized program!
