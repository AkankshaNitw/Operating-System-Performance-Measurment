#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#define LOOPS 50000

typedef unsigned long long ticks;

static __inline__ ticks getCycles(void)
{
    unsigned a, d;
    asm("cpuid");
    asm volatile("rdtsc" : "=a" (a), "=d" (d));
    return (((ticks) a) | (((ticks) d) << 32));
}

int functionWithZeroArguments ();
int functionWithOneArgument (int arg1);
int functionWithTwoArguments (int arg1, int arg2);
int functionWithThreeArguments (int arg1, int arg2, int arg3);
int functionWithFourArguments (int arg1, int arg2, int arg3, int arg4);
int functionWithFiveArguments (int arg1, int arg2, int arg3, int arg4, int arg5);
int functionWithSixArguments (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
int functionWithSevenArguments (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);

int functionWithZeroArguments()
{
    return 10;
}

int functionWithOneArgument(int arg1)
{
    return 10;
}

int functionWithTwoArguments (int arg1, int arg2)
{
    return 10;
}

int functionWithThreeArguments (int arg1, int arg2, int arg3)
{
    return 10;
}

int functionWithFourArguments (int arg1, int arg2, int arg3, int arg4)
{
    return 10;
}

int functionWithFiveArguments (int arg1, int arg2, int arg3, int arg4, int arg5)
{
    return 10;
}

int functionWithSixArguments (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    return 10;
}

int functionWithSevenArguments (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7)
{
    return 10;
}

int main()
{
    ticks startCycle[8], endCycle[8], cyclesPerLoop[8], totalCycles[8], averageCycles[8];
    unsigned timePerLoop[8], averageTime[8];
    int result[8];
    int arg[7];
    unsigned int i;

    for (i=0; i<7; i++)
    {
        arg[i] = rand();
    }

    for (i=0; i<8; i++)
    {
        totalCycles[i] = 0;
    }

    for (i=0; i<LOOPS; i++)
    {
        //Overhead of procedure call with 0 arguments
        //printf("Procedure call with 0 arguments:\n");
        startCycle[0] = getCycles();
        //printf("Start tick: %llu\n", startCycle[0]);
        result[0] = functionWithZeroArguments();
        endCycle[0] = getCycles();
        //printf("End tick: %llu\n", endCycle[0]);
        cyclesPerLoop[0] = endCycle[0] - startCycle[0];
        //printf ("Cycles per loop: %u\n", cyclesPerLoop[0]);
        totalCycles[0] += cyclesPerLoop[0];
        timePerLoop[0] = (unsigned) (cyclesPerLoop[0]/2.4);
        //printf("Time per loop: %u ns\n", timePerLoop);

        //Overhead of procedure call with 1 argument
        //printf("Procedure call with 1 argument:\n");
        startCycle[1] = getCycles();
        //printf("Start tick: %llu\n", startCycle[1]);
        result[1] = functionWithOneArgument(arg[0]);
        endCycle[1] = getCycles();
        //printf("End tick: %llu\n", endCycle[1]);
        cyclesPerLoop[1] = endCycle[1] - startCycle[1];
        //printf ("Cycles per loop: %u\n", cyclesPerLoop[1]);
        totalCycles[1] += cyclesPerLoop[1];
        timePerLoop[1] = (unsigned) (cyclesPerLoop[1]/2.4);
        //printf("Time per loop: %u ns\n", timePerLoop);

        //Overhead of procedure call with 2 arguments
        //printf("Procedure call with 2 arguments:\n");
        startCycle[2] = getCycles();
        //printf("Start tick: %llu\n", startCycle[2]);
        result[2] = functionWithTwoArguments(arg[0], arg[1]);
        endCycle[2] = getCycles();
        //printf("End tick: %llu\n", endCycle[2]);
        cyclesPerLoop[2] = endCycle[2] - startCycle[2];
        //printf ("Cycles per loop: %u\n", cyclesPerLoop[2]);
        totalCycles[2] += cyclesPerLoop[2];
        timePerLoop[2] = (unsigned) (cyclesPerLoop[2]/2.4);
        //printf("Time per loop: %u ns\n", timePerLoop);

        //Overhead of procedure call with 3 arguments
        //printf("Procedure call with 3 arguments:\n");
        startCycle[3] = getCycles();
        //printf("Start tick: %llu\n", startCycle[3]);
        result[3] = functionWithThreeArguments(arg[0], arg[1], arg[2]);
        endCycle[3] = getCycles();
        //printf("End tick: %llu\n", endCycle[3]);
        cyclesPerLoop[3] = endCycle[3] - startCycle[3];
        //printf ("Cycles per loop: %u\n", cyclesPerLoop[3]);
        totalCycles[3] += cyclesPerLoop[3];
        timePerLoop[3] = (unsigned) (cyclesPerLoop[3]/2.4);
        //printf("Time per loop: %u ns\n", timePerLoop);

        //Overhead of procedure call with 4 arguments
        //printf("Procedure call with 4 arguments:\n");
        startCycle[4] = getCycles();
        //printf("Start tick: %llu\n", startCycle[4]);
        result[4] = functionWithFourArguments(arg[0], arg[1], arg[2], arg[3]);
        endCycle[4] = getCycles();
        //printf("End tick: %llu\n", endCycle[4]);
        cyclesPerLoop[4] = endCycle[4] - startCycle[4];
        //printf ("Cycles per loop: %u\n", cyclesPerLoop[4]);
        totalCycles[4] += cyclesPerLoop[4];
        timePerLoop[4] = (unsigned) (cyclesPerLoop[4]/2.4);
        //printf("Time per loop: %u ns\n", timePerLoop);

        //Overhead of procedure call with 5 arguments
        //printf("Procedure call with 5 arguments:\n");
        startCycle[5] = getCycles();
        //printf("Start tick: %llu\n", startCycle[5]);
        result[5] = functionWithFiveArguments(arg[0], arg[1], arg[2], arg[3], arg[4]);
        endCycle[5] = getCycles();
        //printf("End tick: %llu\n", endCycle[5]);
        cyclesPerLoop[5] = endCycle[5] - startCycle[5];
        //printf ("Cycles per loop: %u\n", cyclesPerLoop[5]);
        totalCycles[5] += cyclesPerLoop[5];
        timePerLoop[5] = (unsigned) (cyclesPerLoop[5]/2.4);
        //printf("Time per loop: %u ns\n", timePerLoop);

        //Overhead of procedure call with 6 arguments
        //printf("Procedure call with 6 arguments:\n");
        startCycle[6] = getCycles();
        //printf("Start tick: %llu\n", startCycle[6]);
        result[6] = functionWithSixArguments(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5]);
        endCycle[6] = getCycles();
        //printf("End tick: %llu\n", endCycle[6]);
        cyclesPerLoop[6] = endCycle[6] - startCycle[6];
        //printf ("Cycles per loop: %u\n", cyclesPerLoop[6]);
        totalCycles[6] += cyclesPerLoop[6];
        timePerLoop[6] = (unsigned) (cyclesPerLoop[6]/2.4);
        //printf("Time per loop: %u ns\n", timePerLoop);

        //Overhead of procedure call with 7 arguments
        //printf("Procedure call with 7 arguments:\n");
        startCycle[7] = getCycles();
        //printf("Start tick: %llu\n", startCycle[7]);
        result[7] = functionWithSevenArguments(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6]);
        endCycle[7] = getCycles();
        //printf("End tick: %llu\n", endCycle[7]);
        cyclesPerLoop[7] = endCycle[7] - startCycle[7];
        //printf ("Cycles per loop: %u\n", cyclesPerLoop[7]);
        totalCycles[7] += cyclesPerLoop[7];
        timePerLoop[7] = (unsigned) (cyclesPerLoop[7]/2.4);
        //printf("Time per loop: %u ns\n", timePerLoop);
    }

    for(i=0; i<8; i++)
    {
       averageCycles[i] = totalCycles[i]/LOOPS;
       averageTime[i] = (unsigned) (averageCycles[i]/2.4);
       printf ("Average number of cycles for function with %u arguments: %llu\n", i, averageCycles[i]);
       printf("Average time for function with %u arguments: %u ns\n", i, averageTime[i]);
    }

    return 0;
}
