# About SSE & AVX Vectorizations
This course is focused on using the advanced vector parallelization found in newer CPU's. Data vectorization allows the same instruction to be applied to N values at the same time. 
I.e. AVX allows working with 8 floats (32-bits x 8 = 256 bits) at the same time. AVX instructions usually have similar latency and throughput to that of non-vectorized instructions, so this can effectively multiply the throughput of a program.

## Previous Knowledge:
Advanced knowledge of C++ is recommended: code optimization, compiler flags & pragmas, advanced CPU knowledge (latency, throughput, registers, data alignment, cache, etc.), templates, intrinsics and some basic ASM knowledge.

In this Course C++ will be used. Please note that SSE/AVX extensions are available in other languages (FreePascal, C#, Rust, etc.), but they are outside the scope of this course.

## Difficulty Level: 
Expert. This is not a user-friendly Course. Manual vector extensions add many layers of complexity that should be avoided if optimization of linear code is enough.

## Estimated Time:
120 minutes.

## Hardware requirements
Thanks to the virtualization technology at tech.io you'll only need a compatible browser to complete this course.
Nevertheless, to use these technologies in real applications you'll have the following hardware requirements:

-  A processor with SSE or AVX instruction set.
-  An OS with SSE/AVX support.
-  A compiler with SSE/AVX support.

For reference, we assume the course is running on an Intel Haswell CPU, GCC v4.9.2 and Ubuntu Linux 64bit with kernel 4.4.0.

## What will I learn?
Students will learn about automatic and manual vectorization, how to operate with these kind of registers, problems of execution parallelism in vectors and how to tackle them.

## Why should I learn?
Vectorization of code can achieve about 300% to 600% performance increase over linear code.
In high performance programs, this is a noticeable performance boost.

Common usage:
-  Intensive CPU calculations, like multimedia, encoding, and simulations.

