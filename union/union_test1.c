#include <stdlib.h>
#include <stdio.h>
union Data {
   int i;
   int l;
};

#define SZ 8*1024
#define LOOPS 128*1024

int main() {
	//int *a = (int *)malloc(sizeof(int)*SZ);
	union Data *b = (union Data *)malloc(sizeof(union Data)*SZ);
	for (int i = 0; i < SZ; i++) {
		//a[i]=i;
		b[i].i = i;
	}
	unsigned long long t = 0;
	for (int j=0; j < LOOPS; j++) {
		for (int i = 0; i < SZ; i++) {
			//if (i%2 == 0) {
				t += b[i].i;
			//} else {
			//	t += b[i].l;
			//}
		}
	}
	printf("%llu\n", t);
	return 0;
}
