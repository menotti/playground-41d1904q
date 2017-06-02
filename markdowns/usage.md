# SSE & AVX usage

SSE/AVX enabled CPU's have assembler instructions for operating with `XMM` and `YMM` registers. But in most compilers the process is simplified by using intrinsic functions, so programmers don't need to use assembly directly.

## Intrinsic functions

Compilers wrap up assembler instructions as functions, and using them is as easy as calling a function with the right parameters. Sometimes these intrinsic functions are emulated if the CPU doesn't support the instruction set.

SSE/AVX intrinsic functions use the following naming convention:

 ```cpp
 _<vector_size>_<intrin_op>_<suffix>
 ```
 
- `<vector_size>` is `mm` for 128 bit vectors (SSE), `mm256` for 256 bit vectors (AVX and AVX2), and `mm512` for AVX512.
- `<intrin_op>` Declares the operation of the intrinsic function. I.e. `add`, `sub`, `mul`, etc..
- `<suffix>` Indicates the datatype. `ps` is for float, `pd` for double, and `ep<int_type>` is for  integer datatypes: `epi32` for signed 32 bit integer, `epu16` for unsigned 16 bit integer, etc..

You can find all the intrinsic functions in the [Intel Intrinsics Guide](https://software.intel.com/sites/landingpage/IntrinsicsGuide)
It's a complete reference for any intrinsic function available in SSE/AVX, with categories and a search box.
There is also a [x86 Intrinsics Cheat Sheet](https://db.in.tum.de/~finis/x86-intrin-cheatsheet-v2.2.pdf?lang=en)
But it's harder to read because it is more complex.

## Missing functions in SSE/AVX intrinsics

** Lack of integer division **

For some reason, SSE and AVX lack integer division operators. There are some ways to overcome this:

- By calculating the division in linear code. Retrieving the single data, divide them and store again in the vector. This is pretty slow.
- Converting the integer vector to float, divide them, and convert again to integer.
- For known divisors at compile time, there are some magic numbers to convert division by a constant into a multiplication operation. See [libdivide](https://libdivide.com/) and [Exact Division by Constants](http://www.icodeguru.com/Embedded/Hacker's-Delight/077.htm) for more info
- For power of two divisions, using the bit shift operation. Division by integer 2 is the same as a right shift. This can only be done if all the vectors are divided by the same power of two number. Watch out when performing a right shift on signed numbers! Use sign aware bit shifts.

** Lack of trigonometric functions **

There aren't trigonometric functions in vector intrinsic functions. Possible solutions are calculating them with linear code (one by one for each vector value), or creating approximation functions. Taylor Series and Remez approximations give good results.

** Lack of a random number generator **

Additionally, there aren't random number generators for vectors as intrinsics. But it's simple to recreate a good pseudorandom generator from a linear version. Just be sure about the bits used in the pseudorandom number generator. 32 or 64bit RNG are preferred for filling vectors. 


## Performance penalties

**Data Alignment**

Older CPU architectures can't use vectorization unless data is memory aligned to the vector size. Some other CPU's can use unaligned data with some performance penalties. In recent processors the penalty seems to be negligible [Data alignment for speed: myth or reality?](http://lemire.me/blog/2012/05/31/data-alignment-for-speed-myth-or-reality/). 
But just to be safe it could be a good idea to align data if it doesn't add excessive overhead.

In GCC, data alignment can be done with these variable attributes:
 `__attribute__((aligned(16)))`
 `__attribute__((aligned(32)))`

Review [Specifying Attributes of Variables](https://gcc.gnu.org/onlinedocs/gcc-3.2/gcc/Variable-Attributes.html) for further information.

I just do: `#define ALIGN __attribute__((aligned(32)))` to simplify the alignment declaration on variables. 
 
**SSE <-> AVX Transition Penalties**

There is another big problem when mixing legacy SSE libraries and the new AVX architecture. Because XMM and YMM share the lower 128 bits, transitioning between AVX and SSE can lead to undefined values in the upper 128bits. To solve this, the compiler needs to save the upper 128bits, clear it, execute the old SSE operation, and then restore the old value. This adds a noticeable overhead to AVX operations, resulting in reduced performance.

>**NOTE:** This issue DOESN'T MEAN you can't use \_\_m128 and \_\_m256 at the same time without performance penalties. AVX has a new instruction set for \_\_m128, with VEX prefixes. These new VEX instructions don't have any problem combining with \_\_m256 instructions. The transition penalty is when non-VEX \_\_m128 instructions are combined with \_\_m256 instructions. This happens when you use old SSE libraries linked into new AVX enabled programs.

To avoid transition penalties, the compiler can automatically add calls to `VZEROUPPER` (clears out the upper 128bits) or `VZEROALL` (clears out all the YMM register) with the `-mvzeroupper` parameter, or the programmer can do it manually. If you are not using external SSE libraries, and you are sure all you code is VEX-enabled and compiled with AVX extensions enabled, you can instruct the compiler to avoid adding `VZEROUPPER` calls, with: `-mno-vzeroupper`

Check [Avoiding AVX-SSE Transition Penalties](https://software.intel.com/en-us/articles/avoiding-avx-sse-transition-penalties) and [Why is this SSE code 6 times slower without VZEROUPPER on Skylake?](https://stackoverflow.com/questions/41303780/why-is-this-sse-code-6-times-slower-without-vzeroupper-on-skylake) for additional information.

**Data loading, unloading and shuffling**

Moving data back and forth from AVX registers can be expensive. In some cases, if you have some data stored in linear structures, sending this data to AVX vectors, executing some operations, and recovering this data is more expensive than simply performing calculations a linear way.

Some time ago I tried to simulate some physics in a game, [Codingame's Poker Chip Race](https://www.codingame.com/multiplayer/bot-programming/poker-chip-race), with AVX. This game is based on N circular entities colliding in a 2D space. So in that scenario I needed to calculate up to N*(N-1)/2 possible collisions. My first attempt involved having normal entity classes (with position, radius, etc), and for the collision calculation I shuffled all possible entity collisions in AVX vectors, calculated them in AVX and then returned them back to the entity classes. Once I finished, the results I obtained were mediocre, not more than 30% improvement from linear code, with a lot of overhead and hard to maintain code.  After using a profiler I detected that 90% of the CPU time was being used in data loading and unloading. 

So programmers must take into account the data loading and unloading overhead. Keep in mind that in some cases it becomes a bottleneck.

