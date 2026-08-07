#!/bin/bash


#name="$1"

cd workloads/split-layouts-dtu
make clean
make
make basic_query
mv basic_query ../../rme/overlay/root/
cd ../../



./build_workload.sh rme.json
