#!/bin/bash

echo "Running for figure 9"
./change_config.sh 1 r 1 64
./new_demo1 -q q2 -L -K 136 -O 0,8
cat data/*q2*
./new_demo1 -q q3 -L -K 136 -O 0,8
cat data/*q3*
./new_demo1 -q q4 -L -K 136 -O 0,4,12
cat data/*4*
./change_config.sh 2 r 2 32
./new_demo2 -q q2 -L -K 136 -O 0,8
cat data/*q2*
./new_demo2 -q q3 -L -K 136 -O 0,8
cat data/*q3*
./new_demo2 -q q4 -L -K 136 -O 0,4,12
cat data/*4*
./change_config.sh 4 r 4 16
./new_demo4 -q q2 -L -K 136 -O 0,8
cat data/*q2*
./new_demo4 -q q3 -L -K 136 -O 0,8
cat data/*q3*
./new_demo4 -q q4 -L -K 136 -O 0,4,12
cat data/*4*
./change_config.sh 8 r 8 8
./new_demo8 -q q2 -L -K 136 -O 0,8
cat data/*q2*
./new_demo8 -q q3 -L -K 136 -O 0,8
cat data/*q3*
./new_demo8 -q q4 -L -K 136 -O 0,4,12
cat data/*4*
./change_config.sh 16 r 16 4
./new_demo16 -q q2 -L -K 136 -O 0,8
cat data/*q2*
./new_demo16 -q q3 -L -K 136 -O 0,8
cat data/*q3*
./new_demo16 -q q4 -L -K 136 -O 0,4,12
cat data/*4*

echo "Running for figure 10"
./change_config.sh 4 r 4 4
./new_demo4 -q q2 -L -K 136 -O 0,8
cat data/*q2*
./new_demo4 -q q3 -L -K 136 -O 0,8
cat data/*q3*
./new_demo4 -q q4 -L -K 136 -O 0,4,12
cat data/*4*

./change_config.sh 4 r 4 8
./new_demo4 -q q2 -L -K 136 -O 0,8
cat data/*q2*
./new_demo4 -q q3 -L -K 136 -O 0,8
cat data/*q3*
./new_demo4 -q q4 -L -K 136 -O 0,4,12
cat data/*4*

./change_config.sh 4 r 4 16
./new_demo4 -q q2 -L -K 136 -O 0,8
cat data/*q2*
./new_demo4 -q q3 -L -K 136 -O 0,8
cat data/*q3*
./new_demo4 -q q4 -L -K 136 -O 0,4,12
cat data/*4*

./change_config.sh 4 r 4 32
./new_demo4 -q q2 -L -K 136 -O 0,8
cat data/*q2*
./new_demo4 -q q3 -L -K 136 -O 0,8
cat data/*q3*
./new_demo4 -q q4 -L -K 136 -O 0,4,12
cat data/*4*

./change_config.sh 4 r 4 64
./new_demo4 -q q2 -L -K 136 -O 0,8
cat data/*q2*
./new_demo4 -q q3 -L -K 136 -O 0,8
cat data/*q3*
./new_demo4 -q q4 -L -K 136 -O 0,4,12
cat data/*4*
