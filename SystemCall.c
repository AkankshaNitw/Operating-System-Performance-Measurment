#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#define LOOPS 50000

typedef unsigned long long ticks;

static __inline__ ticks getCycles(void)
{
    unsigned a, d;
    asm("cpuid");
    asm volatile("rdtsc" : "=a" (a), "=d" (d));
    return (((ticks) a) | (((ticks) d) << 32));
}

int main()
{
    pid_t pId;
    unsigned int i;
    ticks startCycle, endCycle, cyclesPerLoop, totalCycles = 0, averageCycles;
    unsigned timePerLoop, averageTime;

    for(i=0; i<LOOPS; i++)
    {
        startCycle = getCycles();
        //printf("Start tick: %llu\n", startCycle);
        pId = getpid();
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
    printf("Average number of cycles for system call: %llu\n", averageCycles);
    printf("Average time for system call: %u ns\n", averageTime);

    return 0;

}
