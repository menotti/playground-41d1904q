#!/bin/bash
# Compile
cmake .
if make > /tmp/compilation_logs 2>&1; then
	echo "CG> redirect-streams \"Test results\""
	# Execute test
	"$@"
	echo "CG> success true"
else
	echo "CG> redirect-streams \"Compilation logs\""
	cat /tmp/compilation_logs
	echo "CG> success false"
fi