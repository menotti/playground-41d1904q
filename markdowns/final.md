# Final Words

On this course you have a good grasp about manual and automatic CPU vectorization:

1. Hardware and software requirements for using SSE and AVX instructions on your code.
2. Vector datatypes available.
3. Information about how to check the autovectorization usage, and hints about loops that can be autovectorized.
4. C++ Vector Frameworks.
5. Masking and conditional load.
6. Controlling the Data Flow.

### Pros and Cons

AVX and SSE vectorization is interesting, and the theorical benefit surpasses any linear optimization:

**Pros**

- Potential gains of 500% to 700% performance versus a linear code.
- Similarities with CUDA, the vectorization programming at GPU level.

**Cons**

- Performance depends on the running hardware.
- Bad performance when there is massive data loading and unloading.
- Data Flow can become very hard to control, and execution time of every data inside a vector affects all the vector execution time. You can't exit early until all data satisfy the exit condition.
- Complex to code.
- Lack of intrinsic functions: Trigonometry, random numbers, integer division.

### Further Courses

*In the works: Link to MarsLander GA using AVX*

### Codingame Multiplayer Games

AVX-enabled simulations can be achieved on some Codingame Multiplayer Games:

- [Coders Strike Back](https://www.codingame.com/multiplayer/bot-programming/coders-strike-back) My AVX version reached between 2.5 and 3.5 Million simulations/turn, with turns of 150 milliseconds. This is done by parallelizing 8 game state simulations at once. An older version with serialized calculations (that is, having data outside AVX, shuffling it inside AVX vectors, calculate, and unload the result) only achieved 600k sims/turn.
- [Poker Chip Racer](https://www.codingame.com/multiplayer/bot-programming/poker-chip-race) Performance is very dependant on number of entities, between 100k and 1.5M sims/turn. Turns are 150ms too.

Many other games can be parallelized and simulated using AVX/SSE vectors.

### Useful links

- [Intel Intrinsics Guide](https://software.intel.com/sites/landingpage/IntrinsicsGuide)
- [x86 Intrinsics Cheat Sheet](https://db.in.tum.de/~finis/x86-intrin-cheatsheet-v2.2.pdf?lang=en)
- [Intel Architectures Developer's Manual](http://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-1-manual.pdf)
- [Agner Fog's Software optimization resources](http://www.agner.org/optimize/)