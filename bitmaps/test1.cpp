#include <stdlib.h>
#include <stdio.h>
#include <bitset>
#include "genutils.h"

#define NL 1000000  

unsigned int f1(unsigned int *arr1, unsigned int *arr2 , unsigned int size) {
	unsigned int ndiff=0;
	for (unsigned int i=0; i<size; i++) {
		if (arr1[i])
			if (arr2[i] != arr1[i])
				ndiff++;
	}
	return ndiff;
}

unsigned int f2(std::bitset<128>& bits, unsigned int *arr1, unsigned int *arr2 , unsigned int size) {
	unsigned int ndiff=0;
	for (unsigned int i=0; i<size; i++) {
		if (bits[i] && (arr1[i]))
			if (arr2[i] != arr1[i])
				ndiff++;
	}
	return ndiff;
}

unsigned int f3(unsigned char *bitmap, unsigned int *arr1, unsigned int *arr2 , unsigned int size) {
	unsigned int ndiff=0;
	for (unsigned int i=0; i<size; i++) {
		unsigned char *p = bitmap + i/8;
		if (*p && (*p >> (i%8) & 1) && (arr1[i]))
			if (arr2[i] != arr1[i])
				ndiff++;
	}
	return ndiff;
}

unsigned int f4(unsigned char *sets, unsigned int *arr1, unsigned int *arr2 , unsigned int size) {
	unsigned int ndiff=0;
	for (unsigned int i=0; i<size; i++) {
		if (sets[i]) {
			unsigned char idx = sets[i] - 1;
			if (arr1[idx])
				if (arr1[idx] != arr2[idx])
					ndiff++;
		}
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
		unsigned char bitmap[128/8];
		unsigned char sets[128];
		for (int i=0; i<sizeof(sets); i++) sets[i] = 0;
		int idx = 0;
		for (unsigned int i=0; i<NE[l]; i++) {
			int r = rand();
			if (r%13==0) {
				a1[i] = r;
				bits.set(i);
				unsigned char *p = bitmap + i/8;
				*p |= 1 << i%8;
				sets[idx] = i+1;
				idx++;
			} else {
				a1[i] = 0;
				bits.reset(i);
				unsigned char *p = bitmap + i/8;
				*p &= ~(1 << i%8);
			}
		}
		if ((a1 == NULL) || (a2 == NULL)) {
			fprintf(stderr,"Unable to alloc memory\n");
			exit(EXIT_FAILURE);
		}
		unsigned long long ndiff = 0;
		std::cerr << "Starting test with " << NE[l] << " elements" << std::endl;
		{
			std::cerr << "Array alone:     ";
			cpu_timer t;
			for (unsigned int i=0; i<NL; i++) {
				ndiff += f1(a1, a2, NE[l]);
			}
		}
		{
			std::cerr << "Array&C++bitmap: ";
			cpu_timer t;
			for (unsigned int i=0; i<NL; i++) {
				ndiff += f2(bits, a1, a2, NE[l]);
			}
		}
		{
			std::cerr << "Array&C bitmap:  ";
			cpu_timer t;
			for (unsigned int i=0; i<NL; i++) {
				ndiff += f3(bitmap, a1, a2, NE[l]);
			}
		}
		{
			std::cerr << "Array & C sets:  ";
			cpu_timer t;
			for (unsigned int i=0; i<NL; i++) {
				ndiff += f4(sets, a1, a2, NE[l]);
			}
		}
		std::cerr << "Ndiff = " << ndiff << std::endl;
		free(a1); a1 = NULL;
		free(a2); a2 = NULL;
	}
	exit(EXIT_SUCCESS);
}
