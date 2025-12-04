#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int printAllBill(bilPosition head) {
	bilPosition headBil = head->nextBil;
	if (headBil == NULL) {
		puts("Fajl nije ucitan.");
		return EXIT_FAILURE;
	}
	artPosition bilEl = NULL;

	while (headBil != NULL) {
		printf("Racun: %d\n", headBil->creationTime);
		bilEl = headBil->firstArt;
		while (bilEl != NULL) {
			printf("-%s\t%.2f\t%d\n", bilEl->name, bilEl->price, bilEl->total);
			bilEl = bilEl->next;
		}
		headBil = headBil->nextBil;
	}

	return EXIT_SUCCESS;
}
