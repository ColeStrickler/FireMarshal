#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define WRITE_BOOL(addr, value)(*(bool*)(addr) = (bool)value)
#define WRITE_UINT8(addr, value)(*(uint8_t*)(addr) = value)
#define WRITE_UINT16(addr, value)(*(uint16_t*)(addr) = value)
#define WRITE_UINT32(addr, value)(*(uint32_t*)(addr) = value)
#define WRITE_UINT64(addr, value)(*(uint64_t*)(addr) = value)

#define READ_BOOL(addr)(*(bool*)(addr))
#define READ_UINT8(addr)(*(uint8_t*)(addr))
#define READ_UINT16(addr)(*(uint16_t*)(addr))
#define READ_UINT32(addr)(*(uint32_t*)(addr))
#define READ_UINT64(addr)(*(uint64_t*)(addr))




#define DTU_UNCACHED_REGION_START	0x180000000ULL
#define RME_START 			0x170000000
#define RME_EN				0x3000000
#define RME_ROWSIZE			(RME_EN + 0x10)
#define RME_EN_COL			(RME_EN + 0x30)
#define RME_COL_WIDTH		(RME_EN + 0x40)
#define RME_COL_OFFSET(i)	(RME_EN + i * 0x10 + 0x48)
#define CACHE_SIZE 1024*1024
#define ROW_COUNT 43690
#define COL_WIDTH 4
#define COL_COUNT 3
#define ROW_SIZE 64

void init_rme_config()
{
	WRITE_UINT32(RME_ROWSIZE, ROW_SIZE);
	while(READ_UINT32(RME_ROWSIZE) != ROW_SIZE);
	WRITE_UINT16(RME_EN_COL, COL_COUNT);
	WRITE_UINT16(RME_COL_WIDTH, COL_WIDTH);
	WRITE_UINT16(RME_COL_OFFSET(0), 0);
	WRITE_UINT16(RME_COL_OFFSET(1), 32);
	WRITE_UINT16(RME_COL_OFFSET(2), 48);
}


void init_data()
{
	// write some initial data
        uint64_t addr = RME_START;
        for (int i = 0;  i < ROW_COUNT; i++)
        {
            *(uint64_t*)addr = 0x1169223344667788;
			*(uint64_t*)(addr + 0x8) = 0x99aabbccddeeff16;
			addr = addr + 0x40;        
		}
}

int flush_cache()
{
	int ret = 0;
	uint64_t addr = 0x160000000;
	for (uint64_t i = 0; i < CACHE_SIZE*3; i += 0x40)
	{
		int value = *(int*)(addr + i);
		ret += value;		
	}
	return ret;
}

int rme_enable()
{
	int ret = *(bool*)(RME_EN);
	*(bool*)(RME_EN) = 1;
	return ret;
}



#define INCLUDE_BOOM_PERF_EXTRA
#ifdef INCLUDE_BOOM_PERF_EXTRA
#define CSR_ROB_FULL        0x020
#define CSR_ROB_EMPTY       0x021
#define CSR_BR_MISPREDICT   0x022
#define CSR_L1I_MISS        0x023
#define CSR_L1D_MISS        0x024
#define CSR_L1D_RELEASE     0x025
#define CSR_ITLB_MISS       0x026
#define CSR_DTLB_MISS       0x027
#define CSR_L2TLB_MISS      0x028
#define CSR_FPISSUE_STALL   0x029
#define CSR_INTISSUE_STALL  0x02a
#endif

#define __STR(x) #x
#define _STR(x)  __STR(x)

#define __read_csr(csr_str) ({               \
    uint64_t __tmp;                          \
    asm volatile ("csrr %0, " csr_str        \
                  : "=r"(__tmp));            \
    __tmp;                                   \
})

#define read_csr(csr) __read_csr(_STR(csr))

static inline uint64_t readData(int col_width, unsigned char* addr)
{
  switch(col_width)
  {
    case 1: return READ_UINT8(addr);
    case 2: return READ_UINT16(addr);
    case 4: return READ_UINT32(addr);
    case 8: return READ_UINT64(addr);
	case 16: return READ_UINT64(addr) + READ_UINT64((uint64_t)addr + 0x8);
    default:
    {

		return 0;
    }
  }
}


void initConfigAGU() 
{
WRITE_UINT8(0x000000000400001c, 6);
WRITE_UINT8(0x000000000400002a, 4);
WRITE_UINT8(0x0000000004000044, 4);
WRITE_UINT8(0x0000000004000062, 2);
WRITE_UINT8(0x000000000400007c, 2);
WRITE_UINT8(0x000000000400009a, 0);

WRITE_UINT32(0x0000000004000168,0x0000000000000000);

WRITE_UINT32(0x0000000004000184,0x000000000000c350);

WRITE_UINT64(0x00000000040002a0,0x0000000100000000);

WRITE_UINT32(0x00000000040002a8,0x0000000000000000);

WRITE_UINT8(0x00000000040002ac,0x0000000000000000);
WRITE_BOOL(0x0000000004000f0c,1);WRITE_UINT64(0x00000000040002b0,0x0000000178000000);
WRITE_UINT8(0x00000000040002b8,0);
WRITE_UINT8(0x0000000004000f01,0x0000000000000001);

WRITE_UINT8(0x0000000004000f02,0x0000000000000001);

WRITE_UINT8(0x0000000004000f03,0x0000000000000001);

WRITE_UINT8(0x0000000004000f04,0x0000000000000000);

}




#define CONF0_ADDR 0x300000000
#define CONF2_ADDR 0x200000000

int main(void)
{





   // switch_to_s_mode();
	//init_rme_config();
	initConfigAGU();
	printf("here\n");
	//init_data();
	//int ret = flush_cache();




	
	/*
		REMEMBER TO CHANGE THIS FOR # OF TOTAL CONFIGS
	*/
	WRITE_UINT64(RME_EN+0x400, RME_START);
	WRITE_UINT64(RME_EN+0x420, 0x0fffffff);
	WRITE_UINT64(RME_EN+0x440, CONF0_ADDR);


	// Config 2
	//WRITE_UINT64(RME_EN+0x410, RME_START+0x4000000);
	//WRITE_UINT64(RME_EN+0x430, 0x0fffffff);
	//WRITE_UINT64(RME_EN+0x450, CONF2_ADDR);

	printf("Hello World\n");
	
	//while(rme_enable() != 1)
	//{
//
	//}
	int f = 0;
	int height = 16;
	int width = 16;
	int batch_size = 8;
	int x = 0;
	for (int c = 0; c < 50000; c++)
	{
			WRITE_UINT32(DTU_UNCACHED_REGION_START+ 0x08000000ULL + c*4, c);
											
	}

	for (int r = 0; r < 50000; r++)
	{
		f += READ_UINT32(CONF0_ADDR + r*4); // test column access streams

	}


	
	printf("hello world %d, %f\n", x, f);
	
	
	
	
	return (int)0;
}


