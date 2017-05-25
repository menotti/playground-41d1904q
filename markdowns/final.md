# Final Words

\o/

### Pros and Cons

**Pros**

- Potential gains 500%-700%

**Cons**

- Depends on hardware
- Complex to code
- Data Flow can become very hard to control

### Further Courses

Link to MarsLander GA using AVX

### Codingame Multiplayer Games

AVX-enabled simulations can be achieved on some Codingame Multiplayer Games

- [Coders Strike Back](https://www.codingame.com/multiplayer/bot-programming/coders-strike-back) My AVX version reached between 2.5 and 3.5 Million simulations/turn, with turns of 150 milliseconds. This is done by parallelizing 8 game state simulations at once. An older version with serialized calculations (that is, having data outside AVX, shuffling it inside AVX vectors, calculate, and unload the result) only achieved 600k sims/turn.
- [Poker Chip Racer](https://www.codingame.com/multiplayer/bot-programming/poker-chip-race) Performance is very dependant on number of entities, between 100k and 1.5M sims/turn. Turns are 150ms too.

I'm pretty sure many other games can be parallelized and simulated on AVX/SSE vectors.

### Useful links

- [Intel Intrinsics Guide](https://software.intel.com/sites/landingpage/IntrinsicsGuide)
- [x86 Intrinsics Cheat Sheet](https://db.in.tum.de/~finis/x86-intrin-cheatsheet-v2.2.pdf?lang=en)
- [Intel Architectures Developer's Manual](http://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-1-manual.pdf)
- [Agner Fog's Software optimization resources](http://www.agner.org/optimize/)