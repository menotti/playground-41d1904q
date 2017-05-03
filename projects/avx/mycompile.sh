#!/bin/bash
# Compile
cd $1
cmake .
if make > /tmp/compilation_logs 2>&1; then
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