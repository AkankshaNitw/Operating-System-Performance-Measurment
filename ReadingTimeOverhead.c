#include<stdio.h>
# define LOOPS 500

typedef unsigned long long ticks;

static __inline__ ticks getCycle(void) {
	unsigned a, d;
	asm volatile ("cpuid");
	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return (((ticks) a) | (((ticks) d) << 32));
}

int main() {
	ticks startCycle, endCycle;
	ticks totalCycle=0;
	unsigned int i;
	unsigned int totalTime;
	for (i = 0; i < LOOPS; i++) {
		startCycle = getCycle();
		endCycle = getCycle();
		totalCycle+=(endCycle - startCycle);
	}
	totalTime=totalCycle/2.4;
	printf ("Total cycle for %i loops: %llu\n", LOOPS, totalCycle);
	printf ("Total time taken for %u loops: %u ns\n", LOOPS, totalTime);
	printf ("Total time taken for single loop: %u ns\n", totalTime/LOOPS);

	return 0;
}



