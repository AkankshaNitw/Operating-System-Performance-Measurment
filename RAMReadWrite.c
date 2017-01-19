#include <stdio.h>
#define LOOP 500

typedef unsigned long long ticks;

static __inline__ ticks getCycle(void) {
	unsigned a, d;
	asm("cpuid");
	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return (((ticks) a) | (((ticks) d) << 32));
}

int main() {
	ticks startCycleForRead, endCycleForRead, startCycleForWrite,
			endCycleForWrite;

	unsigned long long int arrayIndex;
	unsigned long long int totalCycleForRepeatedRead = 0;
	unsigned long long int totalCycleForRepeatedWrite = 0;

	unsigned long long int numberOfElementsInArray = 1024 * 1024 * 4 / sizeof(int);
	int numbers[numberOfElementsInArray];

	for (arrayIndex = 0; arrayIndex < numberOfElementsInArray; arrayIndex++) {
		numbers[arrayIndex] = 0;
	}

	int iForRepeatedRead;
	totalCycleForRepeatedRead = 0;
	for (iForRepeatedRead = 0; iForRepeatedRead < LOOP;
			iForRepeatedRead++) {
		startCycleForRead = getCycle();
		int sumOfElements = numbers[iForRepeatedRead]
				+ numbers[(numberOfElementsInArray / 4) + iForRepeatedRead]
				+ numbers[(numberOfElementsInArray / 2) + iForRepeatedRead];
		endCycleForRead = getCycle();
		//printf("StartCycle for read: %u\n", startCycleForRead);
		//printf("EndCycle for read: %u\n", endCycleForRead);
		unsigned int cycleTakenForRead = endCycleForRead - startCycleForRead;
		//printf("Cycle taken for 3 read: %u\n\n", cycleTakenForRead);
		totalCycleForRepeatedRead = totalCycleForRepeatedRead
				+ cycleTakenForRead;

		int randomVariableForWrite = rand() % numberOfElementsInArray;
		startCycleForWrite = getCycle();
		numbers[randomVariableForWrite] = sumOfElements;
		endCycleForWrite = getCycle();
		//printf("StartCycle for write: %u\n", startCycleForWrite);
		//printf("EndCycle for write: %u\n", endCycleForWrite);
		unsigned long long int cycleTakenForWrite = endCycleForWrite - startCycleForWrite;
		//printf("Cycle taken for 1 write: %u\n\n", cycleTakenForWrite);
		totalCycleForRepeatedWrite = totalCycleForRepeatedWrite
				+ cycleTakenForWrite;

	}

	//printf("\nArray Size: %d MB\n\n", sizeof(numbers) / 1024 / 1024);

	printf("Total cycle per loop for one read: %llu\n", totalCycleForRepeatedRead/LOOP/3);
	printf("Total cycle per loop for one write: %llu\n", totalCycleForRepeatedWrite/LOOP);
}


