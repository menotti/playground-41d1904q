# SSE & AVX usage

SSE/AVX enabled CPU's have assembler instructions for operating with `XMM` and `YMM` registers, but in most compilers the process is simplified by using intrinsic functions, so programmers don't need to use assembler directly.

## Intrinsic functions

Compilers wraps up assembler instructions as functions, and using them is as easy as calling a function with the right parameters. Sometimes these intrinsic functions are emulated if the CPU doesn't have the instruction set.

SSE/AVX intrinsic functions are composed with the following naming:

 ```cpp
 _<vector_size>_<intrin_op>_<suffix>
 ```
 
- `<vector_size>` is `mm` for 128 bit vectors (SSE), `mm256` for 256 bit vectors (AVX and AVX2), and `mm512` for AVX512.
- `<intrin_op>` Declares the operation of the intrinsic function. I.e. `add`, `sub`, `mul`, etc..
- `<suffix>` Indicates the datatype. `ps` is for float, `pd` for double, and `ep<int_type>` is for  integer datatypes: `epi32` for signed 32 bit integer, `epu16` for unsigned 16 bit integer, etc..

You can check all intrinsic functions in [Intel Intrinsics Guide](https://software.intel.com/sites/landingpage/IntrinsicsGuide)
It's a complete reference for any intrinsic function available on SSE/AVX, with categories and a search box.
There is also a [x86 Intrinsics Cheat Sheet](https://db.in.tum.de/~finis/x86-intrin-cheatsheet-v2.2.pdf?lang=en)
But it's harder to review, more complex.

## Lack of Integer division

For some reason SSE and AVX lack integer division operators. There are three ways to overcome this:

1. By calculating the division as linear code. Retrieving the single data, divide them and store again on the vector. This is pretty slow.

2. Converting the integer vector to float, divide them, and convert again to integer.

3. On known divisors at compile time, there are some magic numbers to convert division by constants into multiplications. Check [libdivide](https://libdivide.com/) and [Exact Division by Constants](http://www.icodeguru.com/Embedded/Hacker's-Delight/077.htm) for more info

4. On power of two divisions, using the bit shift operation. Division of integer 2 is the same that a right shift. This can only be done if all the vector is divided by the same power of two number. Watch out with the right shift on signed numbers! Use sign aware bit shifts.

## Performance penalties

**Data Alignment**

Some older CPU architectures can't use vectorization unless data is memory aligned to the vector size. Some other CPU's can use unaligned data with some performance penalties, most recent doesn't have any penalty, so the perfomance may depend on the CPU.

In GCC data alignment can be done with these variable attributes:
 `__attribute__((aligned(16)))`
 `__attribute__((aligned(32)))`

Review [Specifying Attributes of Variables](https://gcc.gnu.org/onlinedocs/gcc-3.2/gcc/Variable-Attributes.html) for further information.

I just do: `#define ALIGN __attribute__((aligned(32)))` to simplify the alignment declaration on variables. 
 
**SSE <-> AVX Transition Penalties**

There is another big problem when mixing legacy SSE libraries and the new AVX architecture. As XMM and YMM shared the lower 128 bits, transition between AVX and SSE can lead to undefined values on the upper 128bits. To solve this, the compiler needs to save the upper 128bits, clear it, execute the old SSE operation, and restore the old value. This adds a noticeable overhead on AVX operations, with reduced performance.

>**NOTE:** This issue DOESN'T MEAN you can't use \_\_m128 and \_\_m256 at the same time without performance penalties. AVX has a new instruction set for \_\_m128, with VEX prefixes. These new VEX instructions don't have any problem mixing it with \_\_m256 instructions. The transition penalty is when non-VEX \_\_m128 instructions are mixed with \_\_m256 instructions. And this happens when you use old SSE libraries linked to new AVX enabled programs.

To avoid transition penalties, the compiler can automatically add calls to `VZEROUPPER` (clears out the upper 128bits) or `VZEROALL` (clears out all the YMM register) with the `-mvzeroupper` parameter, or the programmer can do it manually. If you are not using external SSE libraries, and you are sure all you code is VEX-enabled and compiled with AVX extensions enabled, you can instruct the compiler to avoid adding `VZEROUPPER` calls, with: `-mno-vzeroupper`

Check [Avoiding AVX-SSE Transition Penalties](https://software.intel.com/en-us/articles/avoiding-avx-sse-transition-penalties) and [Why is this SSE code 6 times slower without VZEROUPPER on Skylake?](https://stackoverflow.com/questions/41303780/why-is-this-sse-code-6-times-slower-without-vzeroupper-on-skylake) for additional information.

**Data loading, unloading and shuffling**

Moving data back and forth from AVX registers could be expensive. In some cases if you have some structured data on a non-lineal way, sending this data to AVX vectors, calculate some functions and recovering this data is more expensive that simply calculating it on a linear way.

Some time ago I tried to simulate some physics game [Codingame's Poker Chip Race](https://www.codingame.com/multiplayer/bot-programming/poker-chip-race) with AVX. This game is based on N entities colliding on a 2D space, with circular collisions. So in that scenario I neded to calculate up to N*(N-1)/2 possible collisions. My first attempt was having normal entities classes (with position, radius, etc), and for the collision calculation I'll shuffle all possible entities collisions on AVX vectors, calculate collisions on AVX and return back to entities. Once I finished, the results I obtained were mediocre, not more than 10% improvement from linear code, with a lot of overhead and hard to mantain code.  After using a profiler I detected that 90% of the CPU time was being used on data loading and unloading. 

So programmers must take into account the data loading and unloading overhead, that in some cases it becomes the bottleneck.
