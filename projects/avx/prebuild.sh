#!/bin/bash
chmod 755 run.sh
chmod 755 mycompile.sh
chmod 755 mycompileLOG.sh
cd /project/target
cmake .
make