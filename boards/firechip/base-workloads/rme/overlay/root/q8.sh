#!/bin/bash


echo "Running for figure 8"
./change_config.sh 4 r 4 16
offsets=("0" "0,32" "0,24,48", "0,16,32,48", "0,8,24,32,48", "0,8,16,24,32,58", "0,4,12,16,24,32,48", "4,8,12,20,28,32,48,52", "4,8,12,16,24,32,36,40,48", "4,8,12,16,24,32,36,40,48,56", "4,8,12,16,24,32,36,40,48,52,56,60")
for offset_list in "${offsets[@]}"; do
    echo "Processing offsets: $offset_list"
    ./new_demo4 -q q1 -L -O $offset_list
    cat data/*q1*
done
