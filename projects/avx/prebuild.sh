#!/bin/bash
chmod 755 run.sh
chmod 755 mycompile.sh
cd /project/target
cmake .
make