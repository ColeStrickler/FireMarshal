#!/bin/bash


for o in 1 2 4 8 16 32 64; do
  for d in 1 2 4 8; do
    echo "========================================"
    echo "Running: ./latency -c 0 -m 8192 -t 1 -a dtu_read -o $o -d $d"
    echo "========================================"
    ./latency -c 0 -m 8192 -t 1 -a dtu_read -o $o -d $d
    echo ""
  done
done