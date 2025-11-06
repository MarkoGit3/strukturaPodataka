#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct _postfix;
typedef struct _postfix* Position;
typedef struct _postfix {
	double num;
	Position next;
} Postfix;

int pushNum(Position, double); //upis novih elemenata na vrh stoga
int pop(Position, Position, char); //micanje elementa s vrha stoga te obavljanje operacije
int datIn(Position); //unos stoga

int main() {
    Position head = NULL;
    head = (Position)malloc(sizeof(Postfix));
    if (head == NULL) {
        puts("Neuspjesna alokacija memorije.");
        return EXIT_FAILURE;
    }
    head->next = NULL;
    
    datIn(head);
    printf("\nRezultat iznosi: %f", head->next->num);

    Position temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}

int pushNum(Position p, double val) {
    Position q = (Position)malloc(sizeof(Postfix));
    if (q == NULL) {
        puts("Neuspjesna alokacija memorije.");
        return EXIT_FAILURE;
    }
    q->num = val;
    q->next = p->next;
    p->next = q;
    return EXIT_SUCCESS;
}
int pop(Position p, Position q, char op) {
    switch (op) {
        case('+'):
            p->num = p->num + q->num;
            break;
        case('-'):
            p->num = q->num - p->num;
            break;
        case('*'):
            p->num = p->num * q->num;
            break;
        case('/'):
            if (p->num!=0) {
                p->num = q->num / p->num;
            }
            else {
                puts("Greska.\n");
            }
            break;
        default:
            puts("Greska.\n");
            break;
    }
    p->next = q->next;
    q->next = NULL;
    free(q);
    return EXIT_SUCCESS;    
}
int datIn(Position p) {
    FILE* file = fopen("ListIn.txt", "r");
    if (file == NULL) {
        puts("Fajl nije pronaden.");
        return EXIT_FAILURE;
    }
    char op[20]; //buffer
    double temp;
    int total=0;

    while (fscanf(file, "%s", op) == 1) {
        if (sscanf(op, "%lf", &temp) == 1) {
            total++;
            pushNum(p, temp);
        }
        else if (strchr("+-*/", op[0]) && op[1] == '\0') {
            if (total < 2) {
                puts("Neispravan unos.\n");
                fclose(file);
                return EXIT_FAILURE;
            }
            pop(p->next, p->next->next, *op);
            total--;
        }
        else {
            puts("Neispravan unos.\n");
            fclose(file);
            return EXIT_FAILURE;
        }
    }
    fclose(file);
    return EXIT_SUCCESS;
}