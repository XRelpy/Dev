#include <stdio.h>
#include <stdlib.h>

int unposOnePow(int n) {
	if (n % 2 == 1) {
		return -1;
	} else {
		return 1;
	}
}


int main(int argc, char *argv[]) {
	if (argc != 2) {
		return -1;
	}

	long int n = atol(argv[1]);

	double sum = 0;

	long int i = 0;
	for (; i <= n; i++) {
		sum += (double)unposOnePow(i) / (double)(2 * i + 1);
	}

	printf("Times:%ld \t PI:%.10f\n", n, (sum * 4));
	return 0;
}
