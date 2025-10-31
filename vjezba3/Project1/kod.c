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
Position findEl(Position p); //pronalazi po prezimenu listu prije nje
int addBeg(Position p); //stvara novu listu na pocetku vezane liste
int printEl(Position p); //ispis vezane liste
int addEnd(Position p); //stvara novu listu na kraju vezane liste
int findSur(Position p); //pronalazi nalazi li se zadano prezime u vezanoj listi
int removeEl(Position p); //uklanja element s zadanim prezimenom
int addBeh(Position p); //dodaje novi element iza zadanog
int addInf(Position p); //dodaje novi element ispred zadanog
int sortLis(Position p); //sortira listu po prezimenu
int writeLis(Position p); //upisuje listu u datoteku
int readLis(Position p); //cita listu iz datoteke

int main() {
	int option;
	printf("Odaberi opciju:\n0. Izlaz iz programa.\n1. Dodaj na pocetak liste.\n2. Prikaz liste.\n"
		"3. Dodaj na kraj liste.\n4. Pronadi element.\n5. Ukloni element.\n6. Dodaj iza elementa.\n"
		"7. Dodaj nakon elementa.\n8. Sortiraj listu.\n9. Zapisi listu u dat.\n10. Ucitaj listu iz dat.\n");

	Position head = NULL;
	head = (Position)malloc(sizeof(Student));
	if (head == NULL) {
		puts("Neuspjesna alokacija memorije.");
		return EXIT_FAILURE;
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
			findSur(head->next);
			break;
		case(5):
			removeEl(head);
			break;
		case(6):
			addBeh(head);
			break;
		case(7):
			addInf(head);
			break;
		case(8):
			sortLis(head);
			break;
		case(9):
			writeLis(head);
			break;
		case(10):
			readLis(head);
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
	return EXIT_SUCCESS;
}
Position findEl(Position p) {
	if (p->next == NULL) {
		puts("Prazna lista.");
		return 0;
	}
	char sur[N];
	puts("Trazeno prezime: ");
	scanf("%19s", sur);

	while (p->next != NULL && strcmp(p->next->surname, sur) != 0) {
		p = p->next;
	}

	if (p->next == NULL) {
		puts("Nije pronaden.");
		return 0;
	}

	return p;
}
int addBeg(Position p) {
	Position q = NULL;
	q = (Position)malloc(sizeof(Student));
	if (q == NULL) {
		puts("Neuspjesna alokacija memorije.");
		return EXIT_FAILURE;
	}
	addEl(q);
	q->next = p->next;
	p->next = q;
	return EXIT_SUCCESS;
}
int printEl(Position p) {
	if (p == NULL) {
		puts("Prazna lista.");
		return EXIT_FAILURE;
	}
	else {
		while (p != NULL) {
			printf("%s %s %d\n", p->name, p->surname, p->year);
			p = p->next;
		}
	}
	return EXIT_SUCCESS;
}
int addEnd(Position p) {
	while (p->next != NULL) {
		p = p->next;
	}
	addBeg(p);
	return EXIT_SUCCESS;
}
int findSur(Position p) {
	p = findEl(p);
	p = p->next;

	if (p == NULL) {
		puts("Nije unutar liste.");
		return EXIT_FAILURE;
	}
	else {
		puts("Pronaden je unutar liste.");
	}
	return EXIT_SUCCESS;
}
int removeEl(Position p) {
	if (p->next == NULL) {
		puts("Prazna lista.(removeEl)");
		return 0;
	}
	
	p = findEl(p);
	if (p == NULL || p->next == NULL) {
		return EXIT_FAILURE;
	}
	Position q = p->next;
	p->next = q->next;

	free(q);
	return EXIT_SUCCESS;
}
int addBeh(Position p) {
	p = findEl(p);
	if (p==NULL) {
		return EXIT_FAILURE;
	}
	addBeg(p);
	return EXIT_SUCCESS;
}
int addInf(Position p) {
	p = findEl(p);
	if (p == NULL) {
		return EXIT_FAILURE;
	}
	p=p->next;
	addBeg(p);
	return EXIT_SUCCESS;
}
int sortLis(Position p) {
	if (p->next == NULL || p->next->next == NULL) {
		puts("Manje od 2 clana liste.");
		return EXIT_FAILURE;
	}
	Position P, befP, temp, end;
	end = NULL;
	while (p->next != end) {
		befP = p;
		P = p->next;
		while (P->next != end) {
			if (strcmp(P->surname, P->next->surname)>0) {
				temp = P->next;
				befP->next = temp;
				P->next = temp->next;
				temp->next = P;
				P = temp;
			}
			befP = P;
			P = P->next;
		}
		end = P;
	}
	return EXIT_SUCCESS;
}
int writeLis(Position p) {
	if (p->next==NULL) {
		puts("Nema elemenata za unjeti");
		return EXIT_FAILURE;
	}
	FILE* file = fopen("ListOut.txt", "w");
	if (file == NULL) {
		puts("Fajl nije pronaden.");
		return EXIT_FAILURE;
	}
	
	p = p->next;
	while(p != NULL){
		fprintf(file, "%19s %19s %d\n", p->name, p->surname, p->year);
		p = p->next;
	}

	fclose(file);
	return EXIT_SUCCESS;
}
int readLis(Position p) {
	if (p->next != NULL) {
		puts("Vec postoje elementi u listi.");
		return EXIT_FAILURE;
	}
	FILE* file = fopen("ListIn.txt", "r");
	if (file==NULL) {
		puts("Fajl nije pronaden.");
		return EXIT_FAILURE;
	}
	Position q = p;

	while (1) {
		Position p = (Position)malloc(sizeof(Student));
		if (p == NULL) {
			puts("Nema memorije.");
			fclose(file);
			return EXIT_FAILURE;
		}
		if (fscanf(file, "%19s %19s %d", p->name, p->surname, &p->year)==3) {
			p->next = NULL;
			q->next = p;
			q = p;
		} else {
			free(p);
			break;
		}
	}
	fclose(file);
	return EXIT_SUCCESS;
}