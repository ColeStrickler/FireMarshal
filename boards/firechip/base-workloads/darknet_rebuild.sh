#!/bin/bash


cd workloads/darknet-dtu/

make clean && make


./build_cpp.sh



mkdir -p ../../rme/overlay/root/cfg
mkdir -p ../../rme/overlay/root/data
mkdir -p ../../rme/overlay/root/lib
cp /home/c674s876/Documents/firesim/firesim/.conda-env/riscv-tools/sysroot/lib/libgomp.so.1.0.0 ../../rme/overlay/root/lib/
cp /home/c674s876/Documents/firesim/firesim/.conda-env/riscv-tools/bin/../sysroot/usr/lib/* ../../rme/overlay/root/lib/
cp /home/c674s876/Documents/firesim/firesim/.conda-env/riscv-tools/bin/../sysroot/lib/* ../../rme/overlay/root/lib/
cp opencv-3.4.0/build/install/lib/* ../../rme/overlay/root/lib/
cp ./yolov2-tiny.weights ../../rme/overlay/root
cp data/coco.names ../../rme/overlay/root/data/
cp data/dog.jpg ../../rme/overlay/root/data/dog.jpg
cp cfg/* ../../rme/overlay/root/cfg/
cp libdarknet.so ../../rme/overlay/root/lib/libdarknet.so
cp app ../../rme/overlay/root/darknet_test

cd ../../

./build_workload.sh rme.json
