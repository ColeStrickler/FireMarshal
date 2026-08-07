#!/bin/bash



cd workloads/IsolBench/bench

make clean
make all

rm ../../../rme/overlay/root/bandwidth
mv bandwidth ../../../rme/overlay/root/


cd ../../../


./build_workload.sh ./rme.json
