#ifndef TEST_H
#define TEST_H

struct _CityA;
typedef struct _CityA* cityPosA;
typedef struct _CityA {
	int population;
	char name[30];
	cityPosA right;
	cityPosA left;
}CityA;

struct _CountryA;
typedef struct _CountryA* countryPosA;
typedef struct _CountryA {
	int key;
	char name[30];
	countryPosA nextCountry;
	cityPosA tree;
}CountryA;

struct _HashTable; 
typedef struct _HashTable{
	int size;
	countryPosA* hashList;//sa * valjda
}HashTable;

/*
struct _HashTable;
typedef struct _HashTable* hashList;
typedef struct _HashTable{
	int size;
	Position hashList;
}HashTable;
*/

int cityImportA(cityPosA* temp, char name[]);
int countryImportA(countryPosA* head, HashTable* hash);
cityPosA insertTreeA(cityPosA, cityPosA);
int printCountrysA(countryPosA);
int printCitysA(cityPosA);
countryPosA freeCountrysA(countryPosA);
cityPosA freeCitysA(cityPosA);
int findCountryA(countryPosA);
int findCityA(cityPosA, int);
int primNumber(int);

#endif#pragma once
