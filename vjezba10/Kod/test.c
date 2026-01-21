#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

int countryImportA(countryPosA* temp) {
	countryPosA head = *temp;
	FILE* file = fopen("drzave.txt", "r");
	if (file == NULL) {
		puts("Fajl nije pronaden.");
		return EXIT_FAILURE;
	}
	char buffer[50];
	char name[50];

	while (fscanf(file, "%s %s", name, buffer) == 2) {
		countryPosA newEl = (countryPosA)malloc(sizeof(CountryA));
		if (newEl == NULL) {
			puts("Neuspjesna alokacija memorije.");
			fclose(file);
			return EXIT_FAILURE;
		}
		strcpy(newEl->name, name);
		newEl->tree = NULL;
		head = *temp;		
		while (head->nextCountry != NULL && (strcmp(head->nextCountry->name, newEl->name) < 0)) {
			head = head->nextCountry;
		}
		newEl->nextCountry = head->nextCountry;
		head->nextCountry = newEl;
		cityImportA(&newEl->tree, buffer);
	}

	fclose(file);
	head = (*temp)->nextCountry;
	puts("Pronadene drzava:");
	while (head != NULL) {
		printf("%s\n", head->name);
		head = head->nextCountry;
	}
	puts("");
	return EXIT_SUCCESS;
}
int cityImportA(cityPosA* temp, char name[]) {
	cityPosA* head = temp;
	FILE* file = fopen(name, "r");
	if (file == NULL) {
		puts("Fajl nije pronaden.");
		return EXIT_FAILURE;
	}
	char buffer[100];
	int population;

	while (fscanf(file, " %99[^,],%d", buffer, &population) == 2) {
		cityPosA newEl = (cityPosA)malloc(sizeof(CityA));
		if (newEl == NULL) {
			puts("Neuspjesna alokacija memorije.");
			fclose(file);
			return EXIT_FAILURE;
		}
		strcpy(newEl->name, buffer);
		newEl->left = NULL;
		newEl->right = NULL;
		newEl->population = population;
		*temp = insertTreeA(*temp, newEl);
	}

	fclose(file);
	return EXIT_SUCCESS;
}
cityPosA insertTreeA(cityPosA root, cityPosA newEl)
{
	if (root == NULL) {
		return newEl;
	}
	if (newEl->population < root->population) {
		root->left = insertTreeA(root->left, newEl);
	}
	else if (newEl->population > root->population) {
		root->right = insertTreeA(root->right, newEl);
	}
	else {
		if (strcmp(newEl->name, root->name) < 0) {
			root->left = insertTreeA(root->left, newEl);
		}
		else {
			root->right = insertTreeA(root->right, newEl);
		}
	}
	return root;
}
int printCountrysA(countryPosA temp) {
	if (temp == NULL) {
		puts("Prazna lista.");
		return EXIT_FAILURE;
	}
	countryPosA head = temp->nextCountry;

	int i = 0;

	while (head != NULL) {
		printf("%s\n", head->name);
		printCitysA(head->tree);
		printf("\n");
		head = head->nextCountry;
	}

	return EXIT_SUCCESS;
}
int printCitysA(cityPosA temp) {
	cityPosA root = temp;
	if (root == NULL) {
		return EXIT_SUCCESS;
	}
	printCitysA(root->left);
	printf("%s %d\n", root->name, root->population);
	printCitysA(root->right);
	return EXIT_SUCCESS;
}
countryPosA freeCountrysA(countryPosA head) {
	countryPosA temp;
	while (head != NULL) {
		temp = head;
		head = head->nextCountry;

		freeCitysA(temp->tree);
		free(temp);
	}
	return NULL;
}
cityPosA freeCitysA(cityPosA root) {
	if (root == NULL) {
		return NULL;
	}
	root->left = freeCitysA(root->left);
	root->right = freeCitysA(root->right);

	free(root);
	return NULL;
}

int findCountryA(countryPosA head) {
	if (head == NULL) {
		puts("Prazna lista drzava.");
		return EXIT_FAILURE;
	}
	countryPosA root = head;
	char name[50];
	int value;

	puts("Unesi ime trazene zemlje pa donju granicu populacije.");
	scanf("%s", name);
	scanf("%d", &value);

	while (root != NULL && strcmp(root->name, name) != 0) {
		root = root->nextCountry;
	}
	if(root == NULL){
		puts("Drzava nije pronadena");
		return EXIT_FAILURE;
	}

	printf("Drzava %s lista gradova s vise od %d:\n", root->name, value);
	findCityA(root->tree, value);
	return EXIT_SUCCESS;
}
int findCityA(cityPosA root, int value){
	if (root == NULL) {
		return EXIT_SUCCESS;
	}
	findCityA(root->left, value);
	if (root->population > value) {
		printf("%s %d\n", root->name, root->population);
	}
	findCityA(root->right, value);

	return EXIT_SUCCESS;
}