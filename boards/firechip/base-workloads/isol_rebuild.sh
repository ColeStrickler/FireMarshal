#!/bin/bash



cd workloads/IsolBench/bench/

rm bandwidth.o
rm bandwidth
rm latency.o
rm latency


make all



mv latency ../../../rme/overlay/root
mv bandwidth ../../../rme/overlay/root

cd ../../../

./build_workload.sh rme.json
