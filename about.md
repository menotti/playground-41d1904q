# About SSE & AVX Vectorizations
This course is focused on using the advanced vector parallelization from newer CPU's. Data vectorization allows the same instruction to be applied to N values at the same time. 
I.e. AVX extension allows working with 8 floats (32-bits x 8 = 256 bits) at the same time. AVX instructions usually have similar latency and throughput than non-vectorized instructions, so this can effectively multiply the throughput of a program.

## Previous Knowledge:
It's recommended an advanced C++ knowledge: code optimization, compiler flags & pragmas, advanced CPU knowledge (latency, throughput, registers, data alignment, cache, etc.), templates, intrinsics and some basic ASM knowledge.

In this Course C++ will be used. Please note that SSE/AVX extensions are available on other languages (FreePascal, C#, Rust, etc.), but they are out of scope.

## Difficulty Level: 
Expert. This is not an user-friendly Course. Manual vector extensions adds many layers of complexity that should be avoided if optimization of lineal code is enough.

## Estimated Time:
120 minutes.

## Hardware requeriments
Thanks to the virtualization technology at tech.io you'll only need a compatible browser to complete this course.
Nevertheless, to use these technologies in real applications you'll have the following hardware requeriments:

-  A processor with SSE or AVX instruction set.
-  An OS with SSE/AVX support.
-  A compiler with SSE/AVX support.

For reference, we assume the course is running on an Intel Haswell CPU, GCC v4.9.2 and Ubuntu Linux 64bits with kernel 4.4.0.

## What will I learn?
Students will learn about automatic and manual vectorization, how to operate with these kind of registers, problems of execution parallelism in vectors and how to tackle them.

## Why should I learn?
Vectorization of code can achieve about 300% to 600% performance increase over lineal code.
On high performance programs this is a noticeable performance boost.

Common usage:
-  Intensive CPU calculations, like multimedia, encoding, simulations.



https://tech.io/playgrounds/240/webconsole/content/file-and-directory-management-in-unix-systems
 cat /proc/cpuinfo
 gcc -march=native -dM -E - < /dev/null | egrep "SSE|AVX" | sort


 https://software.intel.com/sites/landingpage/IntrinsicsGuide/
 https://db.in.tum.de/~finis/x86-intrin-cheatsheet-v2.1.pdf
 
 http://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-1-manual.pdf
 