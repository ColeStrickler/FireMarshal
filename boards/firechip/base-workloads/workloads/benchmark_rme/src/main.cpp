#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define RME_BASE 0x110000000
#define SCRATCH_BASE 0x160000000
#define CACHE_SIZE 1024*1024
#define MAX_OFFSET 0xfffffff
#define TWENTYSEVEN_MB 0x1B00000
#define RME_CONFIG 0x3000000

#define WRITE_BOOL(addr, value)(*(bool*)(addr) = value)
#define WRITE_UINT8(addr, value)(*(uint8_t*)(addr) = value)
#define WRITE_UINT16(addr, value)(*(uint16_t*)(addr) = value)
#define WRITE_UINT32(addr, value)(*(uint32_t*)(addr) = value)
#define WRITE_UINT64(addr, value)(*(uint64_t*)(addr) = value)

#define READ_BOOL(addr)(*(bool*)(addr))
#define READ_UINT8(addr)(*(uint8_t*)(addr))
#define READ_UINT16(addr)(*(uint16_t*)(addr))
#define READ_UINT32(addr)(*(uint32_t*)(addr))
#define READ_UINT64(addr)(*(uint64_t*)(addr))


#define RME_START 			0x110000000
#define RME_EN				0x3000000
#define RME_ROWSIZE(base)			(base + 0x10)
#define RME_EN_COL(base)			(base + 0x30)
#define RME_COL_WIDTH(base)		    (base + 0x40)
#define RME_COL_OFFSET(base, i)	    (base + i * 0x10 + 0x48)
#define CACHE_SIZE 1024*1024


void init_rme_config(uint64_t base)
{
	WRITE_UINT32(RME_ROWSIZE(base), 64);
	WRITE_UINT16(RME_EN_COL(base), 1);
	WRITE_UINT16(RME_COL_WIDTH(base), 8);
	WRITE_UINT16(RME_COL_OFFSET(base, 0), 0);
}



void flush_cache(uint64_t base)
{
    for (int i = 0; i < MAX_OFFSET; i += 0x40)
    {
        uint64_t x = *(uint64_t*)((uint64_t)base + i);
    }
}


void enable_rme(uint64_t config)
{
    *(bool*)config = true;
}


int main(int argc, char** argv)
{
    struct timespec time1;
    struct timespec time2;

    struct timespec rme_time1;
    struct timespec rme_time2;

    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Map physical memory into the process's address space
    void* relmem_base = (void*)mmap(NULL, MAX_OFFSET, PROT_READ | PROT_WRITE, MAP_SHARED, fd, RME_BASE);
    if (relmem_base == (void*)MAP_FAILED) {
        perror("mmap");
        close(fd );
        exit(EXIT_FAILURE);
    }

    // Map physical memory into the process's address space
    void* scratch_base = (void*)mmap(NULL, MAX_OFFSET, PROT_READ | PROT_WRITE, MAP_SHARED, fd, SCRATCH_BASE);
    if (scratch_base == (void*)MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Map physical memory into the process's address space
    void* config_base = (void*)mmap(NULL, 0xFFF, PROT_READ | PROT_WRITE, MAP_SHARED, fd, RME_CONFIG);
    if (config_base == (void*)MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }
    init_rme_config((uint64_t)config_base);



    uint64_t sum = 0;
    clock_gettime(CLOCK_MONOTONIC, &time1);
    for (int i = 0; i < TWENTYSEVEN_MB; i += 0x40)
    {
        // read 16 bytes
        sum += *(uint64_t*)((uint64_t)relmem_base + i);
        //sum += *(uint64_t*)(relmem_base + i + 0x8);
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    printf("Raw time: %llu\n", (time2.tv_sec-time1.tv_sec)*1000000000L+(time2.tv_nsec-time1.tv_nsec));

    printf("flushing cache....\n");
    flush_cache((uint64_t)scratch_base);
    printf("cache flushed!\n");
    enable_rme((uint64_t)config_base);
    printf("rme enabled\n");

    sum = 0;
    clock_gettime(CLOCK_MONOTONIC, &rme_time1);
    for (int i = 0; i < TWENTYSEVEN_MB; i += 0x200)
    {
        for (int j = 0; j < 8; j++)
        {
            sum += *(uint64_t*)((uint64_t)relmem_base + i + j*0x8);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &rme_time2);
    printf("RME time: %llu\n", (rme_time2.tv_sec-rme_time1.tv_sec)*1000000000L+(rme_time2.tv_nsec-rme_time1.tv_nsec));
}