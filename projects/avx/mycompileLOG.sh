#!/bin/bash
# Compile
cd $1
compflags=`cat compilerflags.txt | head -n 1`
echo "Compiler Flags are: $compflags"
echo "cmake_minimum_required(VERSION 2.8.9)" > CMakeLists.txt
echo "set(CMAKE_CXX_FLAGS \"$compflags\")" >> CMakeLists.txt
echo "add_executable($1 $1.cpp)" >> CMakeLists.txt
cmake . > /tmp/cmake_logs 2>&1
if make > /tmp/compilation_logs 2>&1; then
    cat /tmp/compilation_logs
	$2 $3 $4
	if [ $? -eq 0 ]
	then
	  echo "CG> success true"
	else
	  echo "CG> success false"
	fi	
else
	echo "CG> redirect-streams \"Compilation logs\""
	cat /tmp/compilation_logs
	echo "CG> success false"
fi