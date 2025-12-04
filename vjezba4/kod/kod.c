#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _poly;
typedef struct _poly* Position;
typedef struct _poly {
	int coef;
	int pow;
	Position next;
} Poly;

int openFile(Position, int);
int addP(Position, Position, Position);
int multiP(Position, Position, Position);
int printP(Position);
int removeP(Position);

int main() {
	int option;
	Poly head = { .coef=0, .pow=0, .next=NULL };
	Poly firstP = { .coef = 0, .pow = 0, .next = NULL };
	Poly secondP = { .coef = 0, .pow = 0, .next = NULL };

	openFile(&firstP, 0);
	openFile(&secondP, 1);

	puts("Izberite opciju:\n1) zbrajanje\n2) mnozenje\n");
	do
	{
		scanf("%d", &option);
		switch (option) {
		case 1:
			addP(&firstP, &secondP, &head);
			break;
		case 2:
			multiP(&firstP, &secondP, &head);
			break;
		default:
			puts("Greska");
		}
	} while (option != 1 && option != 2);

	printP(&firstP);
	printP(&secondP);
	printP(&head);

	removeP(&firstP);
	removeP(&secondP);
	removeP(&head);
	return EXIT_SUCCESS;
}

int openFile(Position head, int opt) {
	FILE* file = NULL;
	if(opt==0){
		file = fopen("prvi.txt", "r");
	}
	else if(opt==1) {
		file = fopen("drugi.txt", "r");
	}
	if (file == NULL) {
		puts("Fajl nije pronaden.");
		return EXIT_FAILURE;
	}
	Position p = head;
	int tempCf, tempPw;
	
	while (fscanf(file, "%d %d", &tempCf, &tempPw) == 2) {
		Position q = (Position)malloc(sizeof(Poly));
		if (q == NULL) {
			puts("Greska pri alokaciji memorije.");
			fclose(file);
			return EXIT_FAILURE;
		}
		q->coef = tempCf;
		q->pow = tempPw;
		p = head;
		while (p->next != NULL && tempPw < p->next->pow) {
			p = p->next;
		}
		q->next = p->next;
		p->next = q;
	}

	fclose(file);
	return EXIT_SUCCESS;
}
int addP(Position firstP, Position secondP, Position p) {
	Position p1 = firstP->next;
	Position p2 = secondP->next;
	Position head;
	int max;
	if (p1->pow >= p2->pow) {
		max = p1->pow;
	} else {
		max = p2->pow;
	}
	
	for (max; max > -1; max--) {
		p1 = firstP->next;
		p2 = secondP->next;
		head = p;

		int val1 = 0, val2 = 0;
		while (p1 != 0) {
			if (p1->pow == max) {
				val1 = p1->coef;
				break;
			}
			p1 = p1->next;
		}
		while (p2 != 0) {
			if (p2->pow == max) {
				val2 = p2->coef;
				break;
			}
			p2 = p2->next;
		}
		int add = val1 + val2;
		if (add != 0) {
			Position q = (Position)malloc(sizeof(Poly));
			if (q == NULL) {
				puts("Greska pri alokaciji memorije.");
				return EXIT_FAILURE;
			}
			while (head->next != NULL && head->next->pow > max) {
				head = head->next;
			}
			q->coef = add;
			q->pow = max;
			q->next = head->next;
			head->next = q;
		}
	}
	puts("Test");
	return EXIT_SUCCESS;
}
int multiP(Position firstP, Position secondP, Position p) {
	Position p1, p2, head;
	
	for (p1 = firstP->next; p1 != 0; p1 = p1->next) {
		for (p2 = secondP->next; p2 != 0; p2 = p2->next) {
			int tempCf = p1->coef * p2->coef;
			int tempPw = p1->pow + p2->pow;

			for (head = p; head->next != 0; head = head->next) {
				if (head->next->pow == tempPw) {
					head->next->coef += tempCf;
					break;
				}
				else if (head->next->pow < tempPw) {
					Position q = (Position)malloc(sizeof(Poly));
					if (q == NULL) {
						puts("Greska pri alokaciji memorije.");
						return EXIT_FAILURE;
					}
					q->coef = tempCf;
					q->pow = tempPw;
					q->next = head->next;
					head->next = q;
					break;
				}
			}
			if (head->next == NULL) {
				Position q = (Position)malloc(sizeof(Poly));
				if (q == NULL) {
					puts("Greska pri alokaciji memorije.");
					return EXIT_FAILURE;
				}
				q->coef = tempCf;
				q->pow = tempPw;
				q->next = NULL;
				head->next = q;
			}
		}
	}

	return EXIT_SUCCESS;
}
int printP(Position p) {
	for (Position q = p->next; q != NULL; q = q->next) {
		printf("%dx%d ", q->coef, q->pow);
	}
	printf("\n");
	return EXIT_SUCCESS;
}
int removeP(Position p) {
	Position temp;
	while (p->next != NULL) {
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}