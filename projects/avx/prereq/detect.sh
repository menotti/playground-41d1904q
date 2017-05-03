#!/bin/bash
#CPU flag detection
echo "****Getting CPU flag capabilities and number of cores"
cat /proc/cpuinfo  | egrep "(flags|model name|vendor)" | sort | uniq -c
#Compiler capabilities. -march=native is required!
echo "****Getting GCC capabilities"
gcc -march=native -dM -E - < /dev/null | egrep "SSE|AVX" | sort 
#OS kernel version
echo "****Getting OS Kernel Version"
uname -a 