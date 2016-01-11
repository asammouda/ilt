#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fact.h>

int main (int argc, char * argv[])
{
	long int n;
	int i;
	if (argc < 2) {
		fprintf(stderr, "usage: %s valeurs...\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	for (i = 1; i < argc; i ++)
		if (sscanf(argv[i], "%ld", & n) == 1)
			fprintf(stdout, "%ld! = %ld\n", n, factorielle(n));
	return EXIT_SUCCESS;
}

