# What is SSE and AVX?

## History

In last years CPU reached some physical and power limitations, so CPU speeds don't have a noticeable change in Ghz.
As computation requeriments continues increasing, chip designers decided to solve this problem with two solutions:

-  Adding more cores. This way Operating Systems can distribute running application to different cores. Also programs can create multiple threads to maximize core usage.
-  Adding vector operations to each core. This solution allows to execute the same instructions to a vector of data. This can only be done inside each application.

Vector registers started in 1997 with MMX instruction set, having 80-bit registers. After that SSE instruction sets were released (several versions of them, from SSE1 to SEE4.2), with 128-bit registers.
In 2011 Intel released the Sandy Bridge architecture, with AVX instruction set (256-bit registers).
Last year the first AVX-512 CPU was released, with 512-bit registers (up to 16x 32-bit floats vector).

In this Course we'll focus both SSE and AVX instruction sets, because they are commonly found on recent processors.

## SSE & AVX Registers

SSE & AVX have 16 register each one. On SSE they are referred as XMM0-XMM15, and on AVX they are YMM0-YMM15. XMM registers are 128bit long, whereas YMM are 256 bit.

![SSE & AVX Registers](avx.png)


>**NOTE:** XMM and YMM overlays! XMM registers are treated as the lower half of the corresponding YMM register. This brings some performance problems when mixing SSE and AVX code.

## Performance penalties

