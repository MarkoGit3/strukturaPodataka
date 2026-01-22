/*
Prepraviti zadatak 10 na nacin da se formira hash tablica drzava. 
Tablica ima 11 mjesta, a funkcija za preslikavanje kljuc racuna 
da se zbraja ASCII vrijednost prvih pet slova drzave zatim racuna 
ostatak cjelobrojnog dijeljenja te vrijednosti s velicinom tablice. 
Drzave s istim kljucem se pohranjuju u vezanu listu sortiranu po nazivu drzave. 
Svaki cvor vezane liste sadrzi stablo gradova 
sortirano po broju stanovnika, zatim po nazivu grada.
vec napravia
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

int main() {
	int size = 11;
	HashTable hashTable;
	hashTable.size = primNumber(size);
	hashTable.hashList = (countryPosA*)malloc(sizeof(countryPosA*) * size);
	if (hashTable.hashList == NULL) {
		puts("Nema memorije");
		return EXIT_FAILURE;
	}
	for (int i = 0; i < hashTable.size; i++) {
		hashTable.hashList[i] = NULL;
	}
	countryImportA(&hashTable, size);
	printCountrysA(&hashTable);
	//findCountryA();

	freeCountrysA(&hashTable);
	return EXIT_SUCCESS;
}
