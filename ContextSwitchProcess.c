#include <stdio.h>
#include <sched.h>
#include <string.h>
#define LOOPS 10000

typedef unsigned long long ticks;

static __inline__ ticks getCycle(void) {
	unsigned a, d;
	asm("cpuid");
	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return (((ticks) a) | (((ticks) d) << 32));
}

int main() {
	int fPipe[2];
	int sPipe[2];
	char parentText[] = "Written by parent!";
	char childText[] = "Written by child!";
	char childTemp[20];
	char parentTemp[20];
	int i;
	ticks startCycle, endCycle;

	if (pipe(fPipe) == -1) {
		printf("Parent: fPipe creation faileds\n");
		return -1;
	}

	if (pipe(sPipe) == -1) {
		printf ("Parent: sPipe creation failed\n");
		return -1;
	}

	startCycle = getCycle();

	int returnedPID=fork();
	if (returnedPID == -1)
		{printf ("Error while forking");
		return -1;
		}
	else {
		//printf("Start Tick: %llu\n", startCycle);
		if (returnedPID == 0) {
			//printf("Child's PID: %d\n", getpid());
			for (i = 0; i < LOOPS; i++) {
				read(fPipe[0], childTemp, sizeof(childTemp));
				//printf("Child %i: Received from fPipe: %s\n", i, childTemp);
				//printf("Child %i: Writing to sPipe\n", i);
				write(sPipe[1], childText, strlen(childText) + 1);
			}
		} else {
			//printf("Parent's PID: %d\n", getpid());

			for (i = 0; i < LOOPS; i++) {
				//printf("Parent %i: Writing to fPipe\n", i);
				write(fPipe[1], parentText, strlen(parentText) + 1);
				read(sPipe[0], parentTemp, sizeof(parentTemp));
				//printf("Parent %i: Received from sPipe: %s\n", i, parentTemp);
			}

			endCycle = getCycle();
			//printf("\n\nStart Tick: %llu\n", startCycle);
			//printf("End Tick: %llu\n", endCycle);

			printf("Total cycle per loop: %llu\n", (endCycle - startCycle)/(LOOPS*2));
		}
	}
	return 0;
}


