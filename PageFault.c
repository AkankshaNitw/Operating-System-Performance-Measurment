#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>
#include <string.h>
#define LOOPS 50000


typedef unsigned long long ticks;
void* address;

static __inline__ ticks getCycles(void)
{
    unsigned a, d;
    asm("cpuid");
    asm volatile("rdtsc" : "=a" (a), "=d" (d));
    return (((ticks) a) | (((ticks) d) << 32));
}

void signalHandler (int sigNo)
{
    if(sigNo == SIGSEGV)
        address = mmap((void*)0x9000000, 4096, PROT_READ | PROT_WRITE , MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
}

int main()
{
    unsigned int i;
    ticks startCycle, endCycle, cyclesPerLoop, totalCycles = 0, averageCycles;
    unsigned timePerLoop, averageTime;
    struct sigaction sigAct;

    if (signal(SIGSEGV, signalHandler) == SIG_ERR)
         printf("\ncan't catch SIGINT\n");

    address = mmap((void*)0x9000000, 4096, PROT_READ | PROT_WRITE , MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    //printf("Address mapped is %s\n", (char *)address);
    munmap(address, 4096);

    for(i=0; i<LOOPS; i++)
    {
        startCycle = getCycles();
        //printf("Start tick: %llu\n", startCycle);
        strncpy(address, "This causes a page fault",24);
        endCycle = getCycles();
        //printf("End tick: %llu\n", endCycle);
        cyclesPerLoop = endCycle - startCycle;
        //printf("Cycles per loop: %llu\n", cyclesPerLoop);
        totalCycles += cyclesPerLoop;
        timePerLoop = (unsigned) (cyclesPerLoop/2.4);
        //printf("Time per loop: %u ns\n", timePerLoop);
    }

    averageCycles = totalCycles/LOOPS;
    averageTime = (unsigned) (averageCycles/2.4);
    printf("Average number of cycles for page fault: %llu\n", averageCycles);
    printf("Average time for page fault: %u ns\n", averageTime);

    return 0;
}


