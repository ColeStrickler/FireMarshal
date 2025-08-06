#!/bin/bash


if [ "$#" -ne 1 ]; then
    echo "Usage: ./build_workload.sh <workload.json>"
    exit -1
fi

#sudo bash -c "ulimit -n 100000 && marshal -v build \"$1\""
sudo marshal -v build $1
sudo marshal -v install $1
