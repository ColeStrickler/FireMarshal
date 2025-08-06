#define _GNU_SOURCE
#include <sys/mman.h>
#include <fcntl.h>
#include <string>
#include <cassert>
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include "agu_dtl/src/dtl_api.hpp"

#define RME_CONFIG                  0x3000000
#define RME_CONFIG_SIZE             0xfff
#define RELCACHE_ADDR               0x110000000UL
#define RELCACHE_SIZE               0x00fffffffUL
#define RME_CONFIG                  0x3000000
#define RME_CONFIG_SIZE             0xfff
#define RME_EN(base)				((uint64_t)base)
#define RME_ROWSIZE(base)			((uint64_t)base + 0x10)
#define RME_EN_COL(base)			((uint64_t)base + 0x30)
#define RME_COL_WIDTH(base)		    ((uint64_t)base + 0x40)
#define RME_COL_OFFSET(base, i)	    ((uint64_t)base + i * 0x10 + 0x48)
#define RME_RESET(base)             ((uint64_t)base + 16 * 0x10 + 0x48)
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
#define KB 1024
#define MB 1024*KB
#define GB 1024*MB
#define CACHESIZE 1*MB

volatile void flush_cache() {
    char *array = (char*)malloc(8*CACHESIZE);

    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
    }
    memset(array, 0, 8*CACHESIZE);

    for (int i = 0; i <8*CACHESIZE; ++i) {
        char value = array[i];
    }
    free(array);
}


// a naive matrix multiplication implementation. 
void matmult_opt0_naive(float *A, float *B, float *C, int dimension)
{
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            for(int k = 0; k < dimension; k++) {
                C[dimension*i+j] += (A[dimension*i+k] * B[dimension*k+j]);
            }
        }
    }	
}

// matrix multiplication with jk order switch
void matmult_opt1_jk(float *A, float *B, float *C, int dimension)
{
    for(int i = 0; i < dimension; i++) {
        for(int k = 0; k < dimension; k++) {
            for(int j = 0; j < dimension; j++) {
                C[dimension*i+j] += (A[dimension*i+k] * B[dimension*k+j]);
            }
        }
    }	
}

// matrix multiplication with jk order switch and tiling    
void matmult_opt2_jk_tiling(float *A, float *B, float *C, int dimension)
{
    int i,j,k,ii,jj,kk;
    int bs = 64; // block size = 32*32*4 = 4KB

    for(i = 0; i < dimension; i+=bs) {
        for(k = 0; k < dimension; k+=bs) {
            for(j = 0; j < dimension; j+=bs) {
                for(ii = i; ii < i+bs; ii++) {
                    for(kk = k; kk < k+bs; kk++) {
                        for(jj = j; jj < j+bs; jj++) {
                            C[dimension*ii+jj] += (A[dimension*ii+kk] * B[dimension*kk+jj]);
                        }
                    }
                }
            }
        }
    }
}   


// transpose matrix
void transpose_naive(float *src, float *dst, int src_row, int src_col)
// src: m(src_row) x n(src_col)  -> dst: n x m
{
    for (int i = 0; i < src_col; i++) {
        for (int j = 0; j < src_row; j++) {
            dst[i*src_row+j] = src[j*src_col+i];
        }
    }
}

// matrix multiplicaiton after transposed
void matmult_opt3_transposed(float *A, float *B, float *C, int dimension)
{
    int i,j,k;
    int alloc_size = dimension*dimension*sizeof(float);
    float *Bt = (float*)malloc(alloc_size);
    transpose_naive(B, Bt, dimension, dimension);

    for(i = 0; i < dimension; i++) {
        for(j = 0; j < dimension; j++) {
            for(k = 0; k < dimension; k++) {                            
                C[dimension*i+j] += (A[dimension*i+k] * Bt[dimension*j+k]);
            }
        }
    }
    free(Bt);
}

float* alloc_matrix(int dim)
{
    return new float[dim*dim];
}

void init_data(float *A, float *B, float *C, int dimension)
{
    int i, j, k;
    srand(292);
    for(i = 0; i < dimension; i++) {
        for(j = 0; j < dimension; j++) {
            A[dimension*i+j] = (float)rand()/(float)(RAND_MAX) - 0.5;
            B[dimension*i+j] = (float)rand()/(float)(RAND_MAX) - 0.5;
            C[dimension*i+j] = 0.0;
        }
        // printf("%f %f\n", A[dimension*i+j], B[dimension*i+j]);
    }
}

void check_eq(float* A, float* B, int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            assert(A[dimension*i + j] == B[dimension*i + j]);
        }
    }
}



std::string FileToString(const std::string& file_)
{
  std::ifstream file(file_);
    if (!file) {
        std::cerr << "Failed to open file\n";
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();  // Read entire file into the buffer
    std::string contents = buffer.str();
    return contents;
}

int open_fd() {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        printf("Can't open /dev/mem.\n");
        exit(0);
    }
    return fd;
}

#define DIMENSION 1300
int main()
{
    auto a = alloc_matrix(DIMENSION);
    auto b = alloc_matrix(DIMENSION);
    auto out1 = alloc_matrix(DIMENSION);
    auto out2 = alloc_matrix(DIMENSION);
    auto out3 = alloc_matrix(DIMENSION);
    init_data(a, b, out1, DIMENSION);
    auto start = std::chrono::high_resolution_clock::now();
    matmult_opt0_naive(a, b, out1, DIMENSION);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
    

    a = alloc_matrix(DIMENSION);
    b = alloc_matrix(DIMENSION);
    init_data(a, b, out2, DIMENSION);
    start = std::chrono::high_resolution_clock::now();
    matmult_opt1_jk(a, b, out2, DIMENSION);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;




    a = alloc_matrix(DIMENSION);
    b = alloc_matrix(DIMENSION);
    init_data(a, b, out3, DIMENSION);
    start = std::chrono::high_resolution_clock::now();
    matmult_opt2_jk_tiling(a, b, out3, DIMENSION);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

    check_eq(out1, out2, DIMENSION);
    int hpm_fd = open_fd();
    unsigned long *config =     (unsigned long*)mmap(NULL, RME_CONFIG_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, hpm_fd, RME_CONFIG);
    void* agu_config_base =  mmap(NULL, 0xfff, PROT_READ|PROT_WRITE, MAP_SHARED, hpm_fd, 0x4000000);  
    assert(agu_config_base != nullptr);        
    unsigned char *plim = (unsigned char*)mmap((void *)0,
                             RELCACHE_SIZE,
                             PROT_READ | PROT_WRITE,
                             MAP_SHARED,
                             hpm_fd,
                             RELCACHE_ADDR);
    auto hwStat = new DTL::AGUHardwareStat(4, 4, 5, 6, 6, 4, 8);
    DTL::API api(hwStat);
    api.SetBaseAddr((uint64_t)agu_config_base);
    if (!api.Compile(FileToString("./aguconfig")))
    {
        printf("Failed to compile dtl program or map onto agu\n");
        return;
    }
    api.ProgramHardware();

    

    auto outrel = alloc_matrix(DIMENSION);
    b = (float*)RELCACHE_ADDR;
    a = alloc_matrix(DIMENSION);


    
    WRITE_BOOL(RME_EN(config), 1);
    printf("Wrote config!\n");
    while(READ_BOOL(RME_EN(config)) != 1)
    {
      printf("Wrote config 0x%x\n", READ_BOOL(RME_EN(config)));
    }




    return 0;
}