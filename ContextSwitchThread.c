#include <stdio.h>
#include <pthread.h>
#include <string.h>
typedef unsigned long long ticks;

int fPipe[2];
int sPipe[2];
char parentText[] = "Written by parent!";
char childText[] = "Written by child!";
char childTemp[20];
char parentTemp[20];
int i;

#define LOOPS 10000

static __inline__ ticks getCycle(void) {
	unsigned a, d;
	asm("cpuid");
	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return (((ticks) a) | (((ticks) d) << 32));
}

void* childProcess(void* arg) {
	for (i = 0; i < LOOPS; i++) {

		//printf("Child %i: In child loop\n", i);
		//printf("Child %i: Read status: %i\n", i,
		read(fPipe[0], childTemp, sizeof(childTemp));
		//printf("Child %i: Received from fPipe: %s\n", i, childTemp);
		//printf("Child %i: Writing to second pipe\n", i);
		//printf("Child %i: Write status: %i\n", i,
		write(sPipe[1], childText, strlen(childText) + 1);
		//printf("Child %i: Written to sPipe\n", i);
	}
	return NULL;
}

int main() {

	pthread_t tId;
	ticks startCycle, endCycle;

	if (pipe(fPipe) == -1) {
		printf("Parent: fPipe creation failed\n");
		return -1;
	}

	if (pipe(sPipe) == -1) {
		printf("Parent: sPipe creation failed\n");
		return -1;
	}

	startCycle = getCycle();

	//clone(&childProcess, (char *) stack + 8192, CLONE_VM, 0);

	int t = pthread_create(&tId, NULL, &childProcess, NULL);
	if (t) {
		printf("Thread creation failed\n");
	}

	for (int i = 0; i < LOOPS; i++) {
		//printf("Parent %i: In parent loop\n", i);
		//printf("Parent %i: Writing to first pipe\n", i);
		//printf("Parent %i: Write status: %i\n", i,
		write(fPipe[1], parentText, strlen(parentText) + 1);
		//printf("Parent %i: Written to first pipe\n", i);
		//printf("Parent %i: Read status: %i\n", i,
		read(sPipe[0], parentTemp, sizeof(parentTemp));
		//printf("Parent %i: Received from second pipe: %s\n", i, parentTemp);
	}
	endCycle = getCycle();
	//printf("\n\nStart Tick: %Ld\n", startCycle);
	//printf("End Tick: %Ld\n", endCycle);

	printf("Cycles per loop: %llu\n", (endCycle - startCycle)/(LOOPS*2));
	//unsigned int time = (unsigned) ((endCycle - startCycle) / 2000);
	//printf("Time in micro sec: %u\n", time);
	//printf("Context switch between two processes: %u micro sec\n", time / 200);

	return 0;
}

