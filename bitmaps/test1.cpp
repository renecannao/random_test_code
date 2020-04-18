#include <stdlib.h>
#include <stdio.h>
#include <bitset>
#include "genutils.h"

#define NL 1000000  

unsigned int f1(volatile unsigned int *arr1, volatile unsigned int *arr2 , unsigned int size) {
	unsigned int ndiff=0;
	for (unsigned int i=0; i<size; i++) {
		if (arr1[i])
			if (arr2[i] != arr1[i])
				ndiff++;
	}
	return ndiff;
}

int main() {
	srand(monotonic_time());
	unsigned int *a1 = NULL;
	unsigned int *a2 = NULL;
	unsigned int NE[4] = { 16, 24, 64, 128 };
	for (unsigned int l=0; l<4; l++) {
		a1 = (unsigned int *)malloc(sizeof(unsigned int*)*NE[l]);
		a2 = (unsigned int *)malloc(sizeof(unsigned int*)*NE[l]);
		std::bitset<128> bits;
		for (unsigned int i=0; i<NE[l]; i++) {
			int r = rand();
			if (r%10==0) {
				a1[i] = r;
				bits.set(i);
			} else {
				a1[i] = 0;
				bits.reset(i);
			}
		}
		if ((a1 == NULL) || (a2 == NULL)) {
			fprintf(stderr,"Unable to alloc memory\n");
			exit(EXIT_FAILURE);
		}
		std::cerr << "Starting test with " << NE[l] << " elements" << std::endl;
		{
			std::cerr << "Array alone: ";
			cpu_timer t;
			for (unsigned int i=0; i<NL; i++) {
				f1(a1, a2, NE[l]);
			}
		}
		free(a1); a1 = NULL;
		free(a2); a2 = NULL;
	}
	exit(EXIT_SUCCESS);
}
