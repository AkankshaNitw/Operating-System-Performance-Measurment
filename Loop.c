#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<time.h>
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
    int j;
    ticks startCycle, endCycle, cyclesPerLoop, totalCycles = 0, averageCycles;
    unsigned timePerLoop, averageTime, i;

    for(i=0; i<LOOPS; i++)
    {
        startCycle = getCycles();
        //printf("Start tick: %Ld\n", startCycle);
        for (j=0; j<1; j++)
        {

        }
        endCycle = getCycles();
        //printf("End tick: %llu\n", endCycle);
        cyclesPerLoop = endCycle - startCycle;
        //printf("Cycles per loop: %llu\n", cyclesPerLoop);
        totalCycles += cyclesPerLoop;
        timePerLoop = (unsigned) (cyclesPerLoop/2.4);
        //printf("Time per loop: %u ms\n", timePerLoop);
    }
    averageCycles = totalCycles/LOOPS;
    averageTime = (unsigned) (averageCycles/2.4);
    printf("Average number of cycles for loop overhead: %llu\n", averageCycles);
    printf("Average time for loop overhead: %u ns\n", averageTime);

    return 0;
}
