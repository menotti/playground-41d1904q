#!/bin/bash
chmod 755 run.sh
chmod 755 ./prereq/detect.sh
cd /project/target
cmake .
make