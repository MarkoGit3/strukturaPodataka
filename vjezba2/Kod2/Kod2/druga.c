#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20

struct _Student;
typedef struct _Student* Position;
typedef struct _Student
{
	char name[N];
	char surname[N];
	int year;
	Position next;
} Student;

int addEl(Position q); //pridodaje vrijednosti novonastaloj listi
int addBeg(Position p); //stvara novu listu na pocetku vezane liste
int printEl(Position p); //ispis vezane liste
int addEnd(Position p); //stvara novu listu na kraju vezane liste
int findEl(Position p); //pronalazi nalazi li se zadano prezime u vezanoj listi
int removeEl(Position p); //uklanja element s zadanim prezimenom

int main() {
	int option;
	puts("Odaberi opciju:\n0. Izlaz iz programa.\n1. Dodaj na pocetak liste.\n2. Prikaz liste.\n3. Dodaj na kraj liste.\n4. Pronadi element.\n5. Ukloni element.");

	Position head = NULL;
	head = (Position)malloc(sizeof(Student));
	if (head == NULL) {
		puts("Neuspjesna alokacija memorije.");
		return 0;
	}
	head->next = NULL;
	
	do {	
		scanf("%d", &option);
		switch (option) {
		case(0):
			break;
		case(1):
			addBeg(head);
			break;
		case(2):
			printEl(head->next);
			break;
		case(3):
			addEnd(head);
			break;
		case(4):
			findEl(head->next);
			break;
		case(5):
			removeEl(head);
			break;

		default:
			puts("Zadana opcija ne postoji.");
			break;
		}
	} while (option != 0);

	Position temp;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}	
	return 0;
}

int addEl(Position q) {
	puts("Unesi ime, prezime i godinu.");
	scanf("%19s", q->name);
	scanf("%19s", q->surname);
	scanf("%d", &q->year);
	return 0;
}
int addBeg(Position p) {
	Position q = NULL;
	q = (Position)malloc(sizeof(Student));
	if (q == NULL) {
		puts("Neuspjesna alokacija memorije.");
		return 0;
	}
	addEl(q);
	q->next = p->next;
	p->next = q;
	return 0;
}
int printEl(Position p) {
	if (p == NULL) {
		puts("Prazna lista.");
		return 0;
	}
	else {
		while (p != NULL) {
			printf("%s %s %d\n", p->name, p->surname, p->year);
			p = p->next;
		}
	}
	return 0;
}
int addEnd(Position p) {
	Position q = NULL;
	q = (Position)malloc(sizeof(Student));
	if (q == NULL) {
		puts("Neuspjesna alokacija memorije.");
		return 0;
	}
	while (p->next != NULL) {
		p = p->next;
	}
	addEl(q);
	q->next = p->next;
	p->next = q;
	return 0;
}
int findEl(Position p) {
	if (p == NULL) {
		puts("Prazna lista.");
		return 0;
	}
	char sur[N];
	puts("Trazeno prezime: ");
	scanf("%19s", sur);

	while (p != NULL && strcmp(p->surname, sur) != 0) {
		p = p->next;
	}

	if (p == NULL) {
		printf("%s nije unutar liste.\n", sur);
		return 0;
	} else {
		printf("%s je unutar liste.\n", sur);
	}
	return 0;
}
int removeEl(Position p) {
	if (p->next == NULL) {
		puts("Prazna lista.");
		return 0;
	}
	char sur[N];
	puts("Izbrisati prezime: ");
	scanf("%19s", sur);
	Position q = p->next;

	while (q != NULL && strcmp(q->surname, sur) != 0)
	{
		p = q;
		q = p->next;
	}
	if (q == NULL){
		puts("Nije pronaden.");
		return 0;
	}
	p->next = q->next;
	
	free(q);
	return 0;
}