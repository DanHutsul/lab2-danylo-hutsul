#!/bin/bash
# OPTIONAL

# Shell script that can be useful for automation some processes.
# For example: 
###
#
#FILE_IN=${argc}[1]
#FILE_OUT=${argc}[2]
#
#mkdir -p build
#mkdir -p bin
#
#cd build
#cmake -G"Unix Makefiles" ..
#make
#cd ../bin/
#chmod u+x main


set -o errexit
set -o nounset
set -o pipefail
