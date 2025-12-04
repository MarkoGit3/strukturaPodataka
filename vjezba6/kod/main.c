#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/library.h"
#define N 50

struct _Article;
typedef struct _Article* artPosition;
typedef struct _Article
{
	char name[N];
	int total;
	float price;
	artPosition next;
} Article;

struct _Bill;
typedef struct _Bill* bilPosition;
typedef struct _Bill
{
	int creationTime;
	bilPosition nextBil;
	artPosition firstArt;

} Bill;

struct _List;
typedef struct _List* listPosition;
typedef struct _List
{
	char name[N];
	listPosition next;
} List;

int importBillList(listPosition); //ucitava listu imena datoteka u kojoj su podaci
int importBillData(listPosition, bilPosition); //ucitava podatke iz datoteke
int freeBill(bilPosition); //oslobodi memorijiu zauzetu od listi 
int printBil(bilPosition); //ispise sve dostupne racune po datumu
int printArt(bilPosition); //ispise odabrani racun
int insertSort(bilPosition, bilPosition); //vezanu listu sortira po datumu
int totalPrice(bilPosition); //ukupna vijednost svih artikala
int printAllBill(bilPosition); //ispise sve racune
int totalPerArticle(bilPosition); //koliko je novca potroseno po artiklu

int main() {
	int option;
	printf("Izaberi opciju:\n0. Izlaz iz programa.\n1. Ucitaj listu dostupnih racuna."
		"\n2. Ucitati dostupne racune.\n3. Ispis distupnih racuna.\n4. Ispis odabranog"
		"racuna.\n5. Sveukupna potrosnja.\n6. Ispis svih racuna.\n"
	);
	listPosition headLis = (listPosition)malloc(sizeof(List));
	if (headLis == NULL) {
		puts("Neuspjesna alokacija memorije.");
		return EXIT_FAILURE;
	}
	headLis->next = NULL;
	bilPosition headBil = (bilPosition)malloc(sizeof(Bill));
	if (headBil == NULL) {
		puts("Neuspjesna alokacija memorije.");
		return EXIT_FAILURE;
	}
	headBil->nextBil = NULL;
	headBil->firstArt = NULL;
	headBil->creationTime = 0;

	do {
		if (scanf("%d", &option) != 1) {
			puts("Neispravan unos.");
			int trash;
			while ((trash = getchar()) != '\n' && trash != EOF) {}
			continue;
		}
		switch (option) {
			case(0):
				break;
			case(1):
				importBillList(headLis);
				break;
			case(2):
				importBillData(headLis, headBil);
				break;
			case(3):
				printBil(headBil);
				break;
			case(4):
				printArt(headBil);
				break;
			case(5):
				totalPrice(headBil);
				break;
			case(6):
				printAllBill(headBil);
				break;
			case(7):
				totalPerArticle(headBil);
				break;
			default:
				puts("Nije medu zadanim opcijama.");
				break;
		}
	} while (option != 0);
	
	listPosition temp;
	while (headLis != NULL) {
		temp = headLis;
		headLis = headLis->next;
		free(temp);
	}
	freeBill(headBil);
	return EXIT_SUCCESS;
}

int importBillList(listPosition head) {
	listPosition tempHead = head;
	FILE* file = fopen("racuni.txt", "r");
	if (file == NULL) {
		puts("Fajl nije pronaden.");
		return EXIT_FAILURE;
	}
	char buffer[200];
	
	while (fscanf(file, "%s", buffer)==1) {
		listPosition newEl = (listPosition)malloc(sizeof(List));
		if (newEl == NULL) {
			puts("Neuspjesna alokacija memorije.");
			fclose(file);
			return EXIT_FAILURE;
		}
		strcpy(newEl->name, buffer);
		newEl->next = NULL;
		tempHead->next = newEl;
		tempHead = newEl;
	}
		
	fclose(file);
	tempHead = head->next;
	puts("Pronadene datoteke:");
	while (tempHead != NULL) {
		printf("%s\n", tempHead->name);
		tempHead = tempHead->next;
	}
	return EXIT_SUCCESS;
}
int importBillData(listPosition head, bilPosition temp) {
	listPosition tempHead = head->next; //koju datoteku ucitat
	if(tempHead == NULL) {
		puts("Fajl nije ucitan.");
		return EXIT_FAILURE;
	}
	bilPosition headBil = temp; //datum
	FILE* file;

	while (headBil->nextBil != NULL)
		headBil = headBil->nextBil;

	while (tempHead != NULL) {
		file = fopen(tempHead->name, "r");
		if (file == NULL) {
		puts("Fajl nije pronaden.");
		return EXIT_FAILURE;
	}
		bilPosition newBil = (bilPosition)malloc(sizeof(Bill));
		if (newBil == NULL) {
			puts("Neuspjesna alokacija memorije.");
			fclose(file);
			return EXIT_FAILURE;
		}
		newBil->firstArt = NULL;

		char tempTime[N];
		if (fscanf(file, "%s", tempTime) != 1) {
			puts("Greska pri formatiranju datuma.");
			fclose(file);
			free(newBil);
			continue;
		}
		int year, month, day;
		if (sscanf(tempTime, "%d-%d-%d", &year, &month, &day) != 3) {
			puts("Greska pri interpretaciji datuma.");
			fclose(file);
			free(newBil);
			continue;
		}
		newBil->creationTime = year * 10000 + month * 100 + day;

		char tempName[N];
		int tempTotal;
		float tempPrice;
		while (fscanf(file, "%s %d %f", tempName, &tempTotal, &tempPrice) == 3) {
			artPosition newArt = (artPosition)malloc(sizeof(Article));
			if (newArt == NULL) {
				puts("Neuspjesna alokacija memorije.");
				fclose(file);
				break;
			}
			strcpy(newArt->name, tempName);
			newArt->total = tempTotal;
			newArt->price = tempPrice;

			newArt->next = newBil->firstArt;
			newBil->firstArt = newArt;
		}
		
		newBil->nextBil = NULL;
		insertSort(headBil, newBil);
		fclose(file);
		tempHead = tempHead->next;
	}
	return EXIT_SUCCESS;
}
int freeBill(bilPosition head) {
	bilPosition tempHead = head;

	while (tempHead != NULL) {
		artPosition tempArt = tempHead->firstArt;
		while (tempArt != NULL) {
			artPosition temp = tempArt;
			tempArt = tempArt->next;
			free(temp);
		}
		bilPosition tempBil = tempHead;
		tempHead = tempHead->nextBil;
		free(tempBil);
	}
	return EXIT_SUCCESS;
}
int printBil(bilPosition head) {
	bilPosition headBil = head->nextBil;
	if (headBil == NULL) {
		puts("Fajl nije ucitan.");
		return EXIT_FAILURE;
	}
	puts("Od najstarijeg:");
	while (headBil != NULL) {
		printf("%d\n", headBil->creationTime);
		headBil = headBil->nextBil;
	}
	return EXIT_SUCCESS;
}
int printArt(bilPosition head) {
	bilPosition headBil = head->nextBil;
	if (headBil == NULL) {
		puts("Fajl nije ucitan.");
		return EXIT_FAILURE;
	}
	int date;
	artPosition bilEl = NULL;

	scanf("%d", &date);
	if (date>=0 && date<=99999999){
		while (headBil != NULL) {
			if (date == headBil->creationTime) {
				bilEl = headBil->firstArt;
				while (bilEl != NULL) {
					printf("%s\t%.2f\t%d\n", bilEl->name, bilEl->price, bilEl->total);
					bilEl = bilEl->next;
				}
				return EXIT_SUCCESS;
			}
			headBil = headBil->nextBil;
		}
		puts("Nije pronaden racun.");
		return EXIT_FAILURE;
	}
	else
	puts("Neispravan datum.");
	return EXIT_FAILURE;
}
int insertSort(bilPosition headBil, bilPosition newBil) {
	bilPosition pre = headBil;
	bilPosition cur = headBil->nextBil;

	while (cur != NULL && (cur->creationTime < newBil->creationTime)) {
		pre = cur;
		cur = cur->nextBil;
	}
	
	newBil->nextBil = cur;
	pre->nextBil = newBil;
	return EXIT_SUCCESS;
}
int totalPrice(bilPosition head) {
	bilPosition headBil = head->nextBil;
	if (headBil == NULL) {
		puts("Fajl nije ucitan.");
		return EXIT_FAILURE;
	}
	float totalPrice=0;
	artPosition bilEl = NULL;

	while (headBil != NULL) {
		bilEl = headBil->firstArt;
		while (bilEl != NULL) {
			totalPrice = totalPrice + bilEl->price * (float)bilEl->total;
			bilEl = bilEl->next;
		}
		headBil = headBil->nextBil;
	}

	printf("Iznosi: %.2f", totalPrice);
	return EXIT_SUCCESS;
}
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
int totalPerArticle(bilPosition head) {
	bilPosition headBil = head->nextBil; //glavna
	if (headBil == NULL) {
		puts("Fajl nije ucitan.");
		return EXIT_FAILURE;
	}
	artPosition bilEl = NULL; //glavna
	artPosition cur = NULL; //trenutna privremena
	artPosition prev = cur; //prosla privremena
	artPosition newEl = NULL; //nova

	while (headBil != NULL) {
		bilEl = headBil->firstArt;
		while (bilEl != NULL) {
			cur = newEl;
			prev = NULL;
			while (cur != NULL) {
				if (strcmp(cur->name, bilEl->name) == 0) {
					cur->total = cur->total + bilEl->total;
					cur->price = bilEl->price;
					break;
				}
				prev = cur;
				cur = cur->next;
			}

			if(cur == NULL){ // ako ne postoji, dodajemo novi element
				artPosition newArt = (artPosition)malloc(sizeof(Article));
				if (newArt == NULL) {
                    puts("Neuspjesna alokacija memorije.");
                    cur = newEl;
					artPosition temp;
                    while (cur != NULL) {
                        artPosition temp = cur;
                        cur = cur->next;
                        free(temp);
                    }
                    return EXIT_FAILURE;
                }
                strcpy(newArt->name, bilEl->name);
				newArt->total = bilEl->total;
				newArt->price = bilEl->price;
				newArt->next = NULL;

                if (newEl == NULL)
                    newEl = newEl;
                else
                    prev->next = newArt;
            }
			bilEl = bilEl->next;
		}
		headBil = headBil->nextBil;
	}

	puts("Ime, ukuno:");
	cur = newEl;
	while (cur != NULL) {
		printf("%s %f\n", cur->name, cur->price);
		cur = cur->next;
	}

	artPosition temp;
	cur = newEl;
	while(cur != NULL){
		temp = cur;
		cur = cur->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}