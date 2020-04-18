#include <stdlib.h>
#include <stdio.h>
#include <bitset>
#include "genutils.h"
#include <string.h>

#define NL 1000000   // number of loops
#define NC 100000      // number of connections
#define MNV 128 // max number of variables . This much be less than 255, because we are using unsigned char as index off by 1

int g_seed = 0;

#ifndef def_fastrand
inline int fastrand() {
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}
#define def_fastrand
#endif


class ConnVars {
	public:
	unsigned int hash[MNV];
	unsigned char sets[MNV];
	std::bitset<MNV> bits;
	unsigned char bitmap[MNV/8+1];
	ConnVars() {
		unsigned char idx = 0;
		memset(bitmap,0,sizeof(bitmap));
		memset(sets,0,sizeof(sets));
		for (unsigned char i=0; i<MNV; i++) {
			unsigned int r = rand();
			if (r%14==0) {
				hash[i]=r;
				sets[idx]=i+1;
				idx++;
				bits.set(i);
				unsigned char *p = bitmap + i/8;
				*p |= 1 << i%8;
			} else {
				hash[i]=0;
				bits.reset(i);
				unsigned char *p = bitmap + i/8;
				*p &= ~(1 << i%8);
			}
		}
	}
	void refreshSets(unsigned char size) {
		memset(sets,0,sizeof(sets));
		unsigned char idx = 0;
		for (unsigned char i=0; i<size; i++) {
			if (hash[i]) {
				sets[idx] = i+1;
				idx++;
			}
		}
	}
};



unsigned int f1(ConnVars *c1, ConnVars *c2 , unsigned int size) {
	unsigned int ndiff=0;
	for (unsigned int i=0; i<size; i++) {
		if (c1->hash[i])
			if (c1->hash[i] != c2->hash[i])
				ndiff++;
	}
	return ndiff;
}

unsigned int f2(ConnVars *c1, ConnVars *c2 , unsigned int size) {
	unsigned int ndiff=0;
	for (unsigned int i=0; i<size; i++) {
		if (c1->bits[i] && (c1->hash[i]))
			if (c1->hash[i] != c2->hash[i])
				ndiff++;
	}
	return ndiff;
}

unsigned int f3(ConnVars *c1, ConnVars *c2 , unsigned int size) {
	unsigned int ndiff=0;
	for (unsigned int i=0; i<size; i++) {
		unsigned char *p = c1->bitmap + i/8;
		if (*p && (*p >> (i%8) & 1) && (c1->hash[i]))
			if (c1->hash[i] != c2->hash[i])
				ndiff++;
	}
	return ndiff;
}

unsigned int f4(ConnVars *c1, ConnVars *c2 , unsigned int size) {
	unsigned int ndiff=0;
	for (unsigned int i=0; i<size; i++) {
		if (c1->sets[i]) {
			unsigned char idx = c1->sets[i] - 1;
			if (c1->hash[idx])
				if (c1->hash[i] != c2->hash[i])
					ndiff++;
		} else {
			return ndiff;
		}
	}
	return ndiff;
}




int main() {
	srand(monotonic_time());
	g_seed = monotonic_time();
	ConnVars **ArrayConns = (ConnVars **)malloc(sizeof(ConnVars *)*NC);
	if (ArrayConns==NULL) {
	fprintf(stderr,"Unable to alloc memory\n");
		exit(EXIT_FAILURE);
	}
	for (unsigned int i=0; i<NC; i++) {
		ConnVars *c = new ConnVars();
		ArrayConns[i] = c;
	}
/*
	unsigned int *a1 = NULL;
	unsigned int *a2 = NULL;
*/
	unsigned int NE[4] = { 16, 24, 64, 128 };
	for (unsigned int l=0; l<4; l++) {
/*
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
*/
		unsigned long long ndiff = 0;
		for (unsigned int i=0; i<NC; i++) {
			ConnVars *c = ArrayConns[i];
			c->refreshSets(NE[l]);
		}
		std::cerr << "Starting test with " << NE[l] << " elements" << std::endl;
		{
			std::cerr << "Array alone:     ";
			cpu_timer t;
			for (unsigned int i=0; i<NL; i++) {
				ConnVars *c1 = ArrayConns[(fastrand()*7)%NC];
				ConnVars *c2 = ArrayConns[(fastrand()*7)%NC];
				ndiff += f1(c1, c2, NE[l]);
			}
		}
		{
			std::cerr << "Array&C++bitmap: ";
			cpu_timer t;
			for (unsigned int i=0; i<NL; i++) {
				ConnVars *c1 = ArrayConns[(fastrand()*7)%NC];
				ConnVars *c2 = ArrayConns[(fastrand()*7)%NC];
				ndiff += f2(c1, c2, NE[l]);
			}
		}
		{
			std::cerr << "Array&C bitmap:  ";
			cpu_timer t;
			for (unsigned int i=0; i<NL; i++) {
				ConnVars *c1 = ArrayConns[(fastrand()*7)%NC];
				ConnVars *c2 = ArrayConns[(fastrand()*7)%NC];
				ndiff += f3(c1, c2, NE[l]);
			}
		}
		{
			std::cerr << "Array & C sets:  ";
			cpu_timer t;
			for (unsigned int i=0; i<NL; i++) {
				ConnVars *c1 = ArrayConns[(fastrand()*7)%NC];
				ConnVars *c2 = ArrayConns[(fastrand()*7)%NC];
				ndiff += f4(c1, c2, NE[l]);
			}
		}
		std::cerr << "Ndiff = " << ndiff << std::endl;
/*
		free(a1); a1 = NULL;
		free(a2); a2 = NULL;
*/
	}
	exit(EXIT_SUCCESS);
}
