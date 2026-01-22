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
	char name[30];
	countryPosA nextCountry;
	cityPosA tree;
}CountryA;

struct _HashTable; 
typedef struct _HashTable{
	int size;
	countryPosA* hashList;
}HashTable;


int cityImportA(cityPosA* temp, char name[]);
int countryImportA(HashTable* hash, int);
cityPosA insertTreeA(cityPosA, cityPosA);
int printCountrysA(HashTable* hash);
int printCitysA(cityPosA);
int freeCountrysA(countryPosA);
cityPosA freeCitysA(cityPosA);
int findCountryA(HashTable* hash);
int findCityA(cityPosA, int);
int primNumber(int);

#endif#pragma once
