#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#define LOOPS 500

typedef long long int ticks;

static __inline__ ticks getCycles(void)
{
    unsigned a, d;
    asm("cpuid");
    asm volatile("rdtsc" : "=a" (a), "=d" (d));
    return (((ticks) a) | (((ticks) d) << 32));
}

void* threadFunction (void* arg)
{
    printf("Thread created successfully!\n");
    return NULL;
}

int main()
{
    int f, w, p, t, fd[LOOPS][2];
    pthread_t tId;
    ticks startCycle, endCycle = 0, cyclesPerLoop, totalCycles1 = 0, totalCycles2 = 0, averageCycles1, averageCycles2;
    unsigned timePerLoop, averageTime1, averageTime2, i;

    //Time to create a process
    printf("Process ID of parent is: %d\n", (int) getpid());
    for(i = 0; i<LOOPS; i++)
    {
        p = pipe(fd[i]);
        if(p<0)
        {
            printf("Pipe failed\n");
        }

        startCycle = getCycles();
        //printf("Start tick: %llu\n", startCycle);
        f = fork();

        if(f == 0)
        {
            endCycle = getCycles();
            //printf("End tick: %llu\n", endCycle);
            //printf("Process ID of child is: %d\n", (int) getpid());
            close(fd[i][0]);
            write(fd[i][1], &endCycle, sizeof(endCycle));
            exit(0);
        }

        else if (f<0)
        {
            printf("Fork failed\n");
        }

        else
        {
            w = wait(NULL);
            close(fd[i][1]);
            read(fd[i][0], &endCycle, sizeof(endCycle));
            //printf("End tick: %llu\n", endCycle);
            cyclesPerLoop = endCycle - startCycle;
            //printf("Cycles per loop: %llu\n", cyclesPerLoop);
            totalCycles1 += cyclesPerLoop;
            timePerLoop = (unsigned) (cyclesPerLoop/2.4);
            //printf("Time per loop: %u ns\n", timePerLoop);
        }
    }

    averageCycles1 = totalCycles1/LOOPS;
    averageTime1 = (unsigned) (averageCycles1/2.4);
    printf("Average number of cycles for new process creation: %llu\n", averageCycles1);
    printf("Average time for new process creation: %u ns\n", averageTime1);

     //Time to create a kernel thread
     for(i=0; i<LOOPS; i++)
     {
         startCycle = getCycles();
         //printf("Start tick: %llu\n", startCycle);
         t = pthread_create(&tId, NULL, &threadFunction, NULL);
         if(t)
         {
             printf("Thread failed!\n");
         }
         endCycle = getCycles();
         //printf("End tick: %llu\n", endCycle);
         cyclesPerLoop = endCycle - startCycle;
         //printf("Cycles per loop: %llu\n", cyclesPerLoop);
         totalCycles2 += cyclesPerLoop;
         timePerLoop = (unsigned) (cyclesPerLoop/2.4);
         //printf("Time per loop: %u ns\n", timePerLoop);
     }

     averageCycles2 = totalCycles2/LOOPS;
     averageTime2 = (unsigned) (averageCycles2/2.4);
     printf("Average number of cycles for new thread creation: %llu\n", averageCycles2);
     printf("Average time for new thread creation: %u ns\n", averageTime2);

     return 0;
}
