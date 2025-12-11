#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#define N 30

struct _Directory;
typedef struct _Directory* dirPosition;
typedef struct _Directory
{
	char name[N];
	dirPosition nextDir;
	dirPosition subDir;
} Directory;

struct _Stack;
typedef struct _Stack* stackPosition;
typedef struct _Stack
{
	stackPosition next; //prosli ubiti
	dirPosition dirLevel;
} Stack;

int createRoot(dirPosition, stackPosition);
int push(stackPosition, dirPosition);
int pop(stackPosition);
int makeDir(dirPosition, char*);
int changeDir(dirPosition, stackPosition, char*);
int listDir(dirPosition);
int deleteDir(dirPosition);
int deleteChild(dirPosition);
int deleteStack(stackPosition);

int main() {	
	int status = 1;
	char option[N];
	char name[N];
	Directory headDir = { .name = "", .nextDir = NULL, .subDir = NULL };
	Stack headStack = { .dirLevel = NULL, .next = NULL };
	createRoot(&headDir, &headStack);

	printf(
		"Program ima sljedece opcije:\n"
		"1 md (ime) - omoguciti unos novih poddirektorija\n"
		"2 cd (ime) - ulaz u poddirektorij\n"
		"3 cd.. - povratak u prethodni direktorij\n"
		"4 dir - ispis sadrzaja direktorija\n"
		"5 exit - gasi program\n"
	);

	while (status) {
		if (scanf("%20s", option) != 1) {
			return EXIT_FAILURE;
		}

		if (strcmp(option, "md") == 0) {
			if (scanf(" %20s", name) != 1) {
				return EXIT_FAILURE;
			}
			makeDir(headStack.next->dirLevel, name);
		}
		else if (strcmp(option, "cd") == 0) {
			if (scanf(" %20s", name) != 1) {
				return EXIT_FAILURE;
			}
			changeDir(headStack.next->dirLevel, &headStack, name);
		}
		else if(strcmp(option, "cd..") == 0){
			pop(&headStack);
		}
		else if (strcmp(option, "dir") == 0){
			listDir(headStack.next->dirLevel);
		}
		else if (strcmp(option, "exit") == 0){
			deleteDir(&headDir);
			deleteStack(&headStack);
			status = 0;
		}
		else {
			puts("Greska pri unosu.");
		}
	}

	return EXIT_SUCCESS;
}

int createRoot(dirPosition head, stackPosition stack){
	dirPosition first = head;
	stackPosition firstStack = stack;
	dirPosition C = (dirPosition)malloc(sizeof(Directory));
	if (C == NULL) {
		puts("Neuospjesna alokacija memorije");
		return EXIT_FAILURE;
	}
	strcpy(C->name, "C");
	while (first->nextDir != NULL) {
		first = first->nextDir;
	}
	//Postavlja ga na kraj
	C->nextDir = first->nextDir;
	first->nextDir = C;
	C->subDir = NULL;
	//dodaje C direktorij na stack
	push(firstStack, C);
	return EXIT_SUCCESS;
}
int push(stackPosition headStack, dirPosition C) {
	stackPosition tempStack = (stackPosition)malloc(sizeof(Stack));
	//postavi prije
	tempStack->next = headStack->next;
	headStack->next = tempStack;
	//dirLevel pokazuje na novi element 
	tempStack->dirLevel = C;

	return EXIT_SUCCESS;
}
int pop(stackPosition stack){
	if (stack->next == NULL) {
		return EXIT_FAILURE;
	}
	stackPosition headStack = stack;
	stackPosition temp = stack->next;
	//uklanjane elemnta s stacka
	headStack->next = temp->next;
	temp->next = NULL;
	
	free(temp);
	return EXIT_SUCCESS;
}
int makeDir(dirPosition C, char* name){
	dirPosition parent = C;
	dirPosition newDir = (dirPosition)malloc(sizeof(Directory));
	if (newDir == NULL) {
		puts("Neuospjesna alokacija memorije");
		return EXIT_FAILURE;
	}
	strcpy(newDir->name, name);

	newDir->nextDir = parent->subDir;
	newDir->subDir = NULL;
	parent->subDir = newDir;

	return EXIT_SUCCESS;
}
int changeDir(dirPosition C, stackPosition headStack, char* name){
	int flag = 0;
	dirPosition temp = C->subDir;
	
	while (temp != 0) {
		if (strcmp(name, temp->name) == 0) {
			push(headStack, temp);
			puts("Pronaden.");
			flag = 1;
			break;
		}
		temp = temp->nextDir;
	}
	
	if (flag == 0) {
		puts("Ne postoji trazeni direktorij.");
	}
	return EXIT_SUCCESS;
}
int listDir(dirPosition curDir){
	dirPosition curSub = NULL;
	int level = 1;

	if (curDir->subDir != NULL) {
		curSub = curDir->subDir;
		while (curSub != NULL) {
			printf("%d%s\n", level, curSub->name);
			level = level + 1;
			listDir(curSub);
			curSub = curSub->nextDir;
		}
	}
	else {
		puts("Direktorij nema djece.");
	}
	
	return EXIT_SUCCESS;
}
int deleteDir(dirPosition head){
	dirPosition headDir = head;
	dirPosition temp;

	while(headDir->nextDir != NULL){
		deleteChild(headDir->subDir);
		temp = headDir->nextDir;
		headDir->nextDir = temp->nextDir;
		temp->nextDir = NULL;
		free(temp);
	}
	
	return EXIT_SUCCESS;
}
int deleteChild(dirPosition child){
	if(child == NULL){
		return EXIT_SUCCESS;
	}
	dirPosition curChild = NULL;
	dirPosition temp;

	if (child->subDir != NULL) {
		curChild = child->subDir;
		while(curChild != NULL){
			deleteChild(curChild);
			temp = curChild->nextDir;
			curChild->nextDir = temp->nextDir;
			temp->nextDir = NULL;
			free(temp);
		}
	}

	return EXIT_SUCCESS;
}
int deleteStack(stackPosition head){
	stackPosition headStack = head;
	stackPosition temp;

	while (headStack->next != NULL) {
		temp = headStack->next;
		headStack->next = temp->next;
		temp->next = NULL;
		free(temp);
	}
	
	return EXIT_SUCCESS;
}