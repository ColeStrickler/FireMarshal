#!/bin/bash



cd workloads/relational-memory-fsim/EDBT

make clean
make

mv new_demo ../../../rme/overlay/root/new_demo$1

cd ../../../

#/./build_workload.sh rme.json


