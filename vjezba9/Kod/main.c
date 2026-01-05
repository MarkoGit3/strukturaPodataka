/*
Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u cvorove binarnog stabla.

a)
Napisati funkciju insert koja dodaje element u stablo
tako da se pozivima te funkcije za sve element zadanog
niza brojeva stvori stablo kao na slici Slika 1.
Funkcije vraca pokazivac na korijen stabla.

b)
Napisati funkciju replace koja ce svaki element stabla zamijeniti
sumom elemenata u njegovom lijevom i desnom podstablu (tj. sumom
svih potomaka prije zamjene vrijednosti u tim potomcima).
Npr. stablo sa slike Slika 1 u stablo na slici Slika 2.

c)
Prepraviti program na nacin da umjesto predefiniranog cjelobrojnog polja
koristenjem funkcije rand() generira slucajne brojeve u rasponu <10, 90>.

Takoder, potrebno je upisati u datoteku sve brojeve u inorder
prolasku nakon koristenja funkcije iz a), zatim b) dijela zadatka.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int main() {
	treePos root = NULL;
	int niz[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	int j = sizeof(niz) / sizeof(int);
	printf("Ukupno elemnata niza: %d\n", j);
	/*for (int i = 0; i < j; i++) {
		niz[i] = rand() % 81 + 10;
		root = insertEl(root, niz[i]);
	}*/

	for (int i = 0; i < j; i++)	{
		root = insertEl(root, niz[i]);
	}
	printInorder(root);
	puts("\nPoslije b dijela:\n");

	if (replaceMulti(root) == NULL) {
		puts("Prazno stablo");
	}
	printInorder(root);

	saveTree(root);

	if (root == NULL) {
		puts("Greska pri unosu.");
		return EXIT_FAILURE;
	}
	freeTree(root);
	return EXIT_SUCCESS;
}
