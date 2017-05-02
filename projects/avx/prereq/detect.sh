#!/bin/bash
#CPU flag detection
cat /proc/cpuinfo  
#Compiler capabilities. -march=native is required!
gcc -march=native -dM -E - < /dev/null | egrep "SSE|AVX" | sort 
#OS kernel version
uname -a 