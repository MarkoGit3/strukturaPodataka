/*10. Napisati program koji cita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih drzava. Uz
ime drzave u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
drzave. Svaka datoteka koja predstavlja drzavu sadrzi popis gradova u formatu naziv_grada,
broj_stanovnika.
a) Potrebno je formirati sortiranu vezanu listu drzava po nazivu. 
Svaki cvor vezane liste sadrzi stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.
b) Potrebno je formirati stablo drzava sortirano po nazivu. 
Svaki cvor stabla sadrzi vezanu listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.

Nakon formiranja podataka potrebno je ispisati drzave i gradove te omoguciti korisniku putem
tastature pretragu gradova odredene drzave koji imaju broj stanovnika veci od unosa na tastaturi.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"


int main() {
	countryPosA head = malloc(sizeof(CountryA));
	if (head == NULL) {
		puts("Nema memorije");
		return EXIT_FAILURE;
	}
	head->nextCountry = NULL;
	head->tree = NULL;
	int option;
	
	printf("Izaberi opciju:\n1. a) nacin nacin rada.\n2. b) nacin nacin rada.\n");
	if (scanf("%d", &option) != 1) {
		puts("Neispravan unos.");
		int trash;
		while ((trash = getchar()) != '\n' && trash != EOF) {}
	}
	switch (option) {
	case(1):
		countryImportA(&head);
		printCountrysA(head);
		findCountryA(head);
		break;
	case(2):
		//importBillData(headLis, headBil);
		break;
	default:
		puts("Nije medu zadanim opcijama.");
		break;
	}

	freeCountrysA(head);
	return EXIT_SUCCESS;
}
