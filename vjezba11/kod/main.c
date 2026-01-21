/*
Prepraviti zadatak 10 na nacin da se formira hash tablica drzava. 
Tablica ima 11 mjesta, a funkcija za preslikavanje kljuc racuna 
da se zbraja ASCII vrijednost prvih pet slova drzave zatim racuna 
ostatak cjelobrojnog dijeljenja te vrijednosti s velicinom tablice. 
Drzave s istim kljucem se pohranjuju u vezanu listu sortiranu po nazivu drzave. 
Svaki cvor vezane liste sadrzi stablo gradova 
sortirano po broju stanovnika, zatim po nazivu grada.

inicijalizirati hashtablicu
//nez jel ovo moran: malloc(sizeof()*size)
//ovo moran: osugiurati primNumber(da je npr 10 nade 11 odnosno do tu se prosiri tablica)
hashtable.size = nextprime(size);
//alocirat head za svaki dio hashTablice
hashTable.hashlist = (Position)malloc(sizeof(position*)*size); //dobije se 10 razlicitih headova za listu drzava
for(int i=0; i<hasttablcle.size; i++){
hashtable->hashlist[i]=NULL
}


KEY=(countryname[0]=...[])%size

b)sortirani unos
if(*(hashTable.hashList)==NULL)
	dodaj novi el
else if(nesto)
	strcmp(countryname,htable<0)
	dodaj novi el
else
while(ht.thislist!=NULL && strcmp(>0))
{
nesto
hashtable.hashlist
}
nesto(dodaj?) novi el
}

c)dodavanje nove?
newEl.key=key
strcpy
newel.next=hashrable.hashlist[findKey]
hashtable.hashlist[findkey]=noviel
*/
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
	int option, key;
	int size = 11;
	
	HashTable hashTable;
	hashTable.size = primNumber(size);
	hashTable.hashList = (countryPosA)malloc(sizeof(countryPosA*) * size);
	for (int i = 0; i < hashTable.size; i++) {
		hashTable.hashList[i] = NULL;
	}




	printf("Izaberi opciju:\n1. a) nacin nacin rada.\n2. b) nacin nacin rada.\n");
	if (scanf("%d", &option) != 1) {
		puts("Neispravan unos.");
		int trash;
		while ((trash = getchar()) != '\n' && trash != EOF) {}
	}
	switch (option) {
	case(1):
		countryImportA(&head, &hashTable);
		printCountrysA(head);
		findCountryA(head);
		break;
	default:
		puts("Nije medu zadanim opcijama.");
		break;
	}

	freeCountrysA(head);
	return EXIT_SUCCESS;
}
