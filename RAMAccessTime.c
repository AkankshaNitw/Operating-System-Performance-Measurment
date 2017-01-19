# include <stdio.h>
# define LOOPS 1000
typedef unsigned long long ticks;

static __inline__ ticks getCycle(void) {
	unsigned a, d;
	asm("cpuid");
	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return (((ticks) a) | (((ticks) d) << 32));
}

int main() {
	ticks startCycle, endCycle;

	unsigned long long int memorySize[] =
			{ 128, 256, 512, 1024, 1024 * 2, 1024 * 4, 1024 * 8, 1024 * 16, 1024
					* 32, 1024 * 64, 1024 * 128, 1024 * 256, 1024 * 512, 1024
					* 1024 * 1, 1024 * 1024 * 2, 1024 * 1024 * 4};

	int indexForMemorySize;
	unsigned long long int arrayIndex;
	unsigned long long int totalCycleForRepeatedRead = 0;
	for (indexForMemorySize = 0; indexForMemorySize < 16; indexForMemorySize++) {
		unsigned int dummyAdd=0;
		unsigned long long int numberOfElementsInArray =
				memorySize[indexForMemorySize] / sizeof(int);
		int numbers[numberOfElementsInArray];

		for (arrayIndex = 0; arrayIndex < numberOfElementsInArray;
				arrayIndex++) {
			numbers[arrayIndex] = arrayIndex%10;
		}

		int iForRepeatedRead;
		totalCycleForRepeatedRead = 0;
		for (iForRepeatedRead = 0; iForRepeatedRead < LOOPS;
				iForRepeatedRead++) {
			int randomNumberForIndex = rand() % numberOfElementsInArray;
			//printf("Random Number: %u\n", randomNumberForIndex);
			startCycle = getCycle();
			int dummyRead=numbers[randomNumberForIndex];
			endCycle = getCycle();
			//printf("StartCycle: %u\n", startCycle);
			//printf("EndCycle: %u\n", endCycle);
			dummyAdd+=dummyRead;
			unsigned int cycleTakenPerRead = endCycle - startCycle;
			//printf("Cycle taken per read: %u\n", cycleTakenPerRead);
			totalCycleForRepeatedRead = totalCycleForRepeatedRead
					+ cycleTakenPerRead;
		}
		if (memorySize[indexForMemorySize] < 1024) {
			printf("MemorySize in B: %llu\n", memorySize[indexForMemorySize]);
		} else if (memorySize[indexForMemorySize] < 1024 * 1024) {
			printf("MemorySize in KB: %llu\n",
					memorySize[indexForMemorySize] / 1024);
		} else {
			printf("MemorySize in MB: %llu\n",
					memorySize[indexForMemorySize] / 1024 / 1024);
		}
		printf ("Dummy Add: %u\n", dummyAdd);
		printf("Total cycle per access: %llu\n", totalCycleForRepeatedRead/LOOPS);
		//unsigned int time = (totalCycleForRepeatedRead) / 2;
		//printf("Time in nano sec: %u\n", time);
		//printf("Time in nano sec per access: %u\n", time / LOOPS);
	}

	return 0;
}


