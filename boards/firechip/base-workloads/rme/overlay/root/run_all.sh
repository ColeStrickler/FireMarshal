#!/bin/bash


chmod +x ./change_config.sh
sed -i 's/row_count = 43690/row_count = 442368/' config
#sed -i 's/row_count = 442368/row_count = 43690/' config
echo "Running for figure 7"
./change_config.sh 1 r 1 64
./new_demo1 -q q1 -L -O 0,24,48
cat data/*q1*
./change_config.sh 2 r 2 32
./new_demo2 -q q1 -L -O 0,24,48
cat data/*q1*
./change_config.sh 4 r 4 16
./new_demo4 -q q1 -L -O 0,24,48
cat data/*q1*
./change_config.sh 8 r 8 8
./new_demo8 -q q1 -L -O 0,24,48
cat data/*q1*
./change_config.sh 16 r 16 4
./new_demo16 -q q1 -L -O 0,32,48
cat data/*q1*

echo "Running for figure 8"
./change_config.sh 4 r 4 16
offsets=("0" "0,32" "0,24,48", "0,16,32,48", "0,8,24,32,48", "0,8,16,24,32,58", "0,4,12,16,24,32,48", "4,8,12,20,28,32,48,52", "4,8,12,16,24,32,36,40,48", "4,8,12,16,24,32,36,40,48,56", "4,8,12,16,24,32,36,40,48,52,56,60")
for offset_list in "${offsets[@]}"; do
    echo "Processing offsets: $offset_list"
    ./new_demo4 -q q1 -L -O $offset_list
    cat data/*q1*
done


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
