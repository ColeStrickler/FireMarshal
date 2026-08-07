#!/bin/bash


cd workloads/matmul

make clean
make

mv dtl_bench ../../rme/overlay/root/


cd src/dtl/dtu-runtime-driver
make clean
make

mv dtu-driver.ko ../../../../../rme/overlay/root/


cd ../../../../../
./build_workload.sh rme.json
