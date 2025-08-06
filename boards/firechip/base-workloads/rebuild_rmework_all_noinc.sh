#!/bin/bash


./rebuildrme_work.sh 1noinc
sed -i 's/#define T[[:space:]]\+unsigned char/#define T unsigned short/' /home/c674s876/Documents/firesim/dtu-firesim/chipyard/software/firemarshal/boards/firechip/base-workloads/workloads/relational-memory-fsim/EDBT/include/config.h



./rebuildrme_work.sh 2noinc
sed -i 's/#define T[[:space:]]\+unsigned short/#define T unsigned int/' /home/c674s876/Documents/firesim/dtu-firesim/chipyard/software/firemarshal/boards/firechip/base-workloads/workloads/relational-memory-fsim/EDBT/include/config.h

./rebuildrme_work.sh 4noinc
sed -i 's/#define T[[:space:]]\+unsigned int/#define T unsigned long/' /home/c674s876/Documents/firesim/dtu-firesim/chipyard/software/firemarshal/boards/firechip/base-workloads/workloads/relational-memory-fsim/EDBT/include/config.h


./rebuildrme_work.sh 8noinc
sed -i 's/#define T[[:space:]]\+unsigned long/#define T __uint128_t/' /home/c674s876/Documents/firesim/dtu-firesim/chipyard/software/firemarshal/boards/firechip/base-workloads/workloads/relational-memory-fsim/EDBT/include/config.h


./rebuildrme_work.sh 16noinc
sed -i 's/#define T[[:space:]]\+__uint128_t/#define T unsigned char/' /home/c674s876/Documents/firesim/dtu-firesim/chipyard/software/firemarshal/boards/firechip/base-workloads/workloads/relational-memory-fsim/EDBT/include/config.h
